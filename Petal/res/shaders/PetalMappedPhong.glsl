#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoords;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

out vec3 v_Normal;
out vec2 v_TexCoords;
out vec3 v_FragmentPosition;

void main()
{
	v_Normal = u_NormalMatrix * a_Normal;
	v_TexCoords = a_TexCoords;
	v_FragmentPosition = vec3(u_Model * vec4(a_Position, 1.0f));
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
}

#type fragment
#version 460 core

struct Material
{
	sampler2D AmbientDiffuse;
	sampler2D Specular;
	float Shininess;
};

struct DirectionalLight
{
	vec3 Direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

struct PointLight
{
	vec3 Position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	// Attenuation values
	float Constant;
	float Linear;
	float Quadratic;
};

in vec3 v_Normal;
in vec2 v_TexCoords;
in vec3 v_FragmentPosition;

uniform Material u_Material;
uniform DirectionalLight u_DirLight;
uniform uint u_NumPointLights;
uniform PointLight u_PointLights[8];
uniform vec3 u_CameraPosition;

layout (location = 0) out vec4 fragColor;

vec3 CalcDirLight(DirectionalLight light, vec3 n, vec3 v);
vec3 CalcPointLight(PointLight light, vec3 n, vec3 v, vec3 fp);

void main()
{
	vec3 n = normalize(v_Normal);
	vec3 v = normalize(u_CameraPosition - v_FragmentPosition);

	vec3 color = vec3(0.0f);
	color += CalcDirLight(u_DirLight, n, v);

	for (int i = 0; i < u_NumPointLights; i++)
		color += CalcPointLight(u_PointLights[i], n, v, v_FragmentPosition);
	
	fragColor = vec4(color, 1.0f);
}

vec3 CalcDirLight(DirectionalLight light, vec3 n, vec3 v)
{
	vec3 l = normalize(-light.Direction);
	vec3 ambient = vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * light.Ambient;

	float diffuseStrength = max(dot(n, l), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * light.Diffuse;

	vec3 r = reflect(-l, n);
	float specularStrength = pow(max(dot(v, r), 0.0f), u_Material.Shininess);
	vec3 specular = specularStrength * vec3(texture(u_Material.Specular, v_TexCoords)) * light.Specular;

	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 n, vec3 v, vec3 fp)
{
	float distance = length(light.Position - fp);
	float attenuation = 1.0f / (light.Constant + light.Linear * distance + light.Quadratic * distance * distance);
	vec3 ambient = vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * light.Ambient;

	vec3 l = normalize(light.Position - fp);
	float diffuseStrength = max(dot(n, l), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * light.Diffuse;

	vec3 r = reflect(-l, n);
	float specularStrength = pow(max(dot(v, r), 0.0f), u_Material.Shininess);
	vec3 specular = specularStrength * vec3(texture(u_Material.Specular, v_TexCoords)) * light.Specular;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return ambient + diffuse + specular;
}
