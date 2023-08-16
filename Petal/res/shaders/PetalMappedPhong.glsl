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
uniform PointLight u_Light;
uniform vec3 u_CameraPosition;

layout (location = 0) out vec4 fragColor;

void main()
{
	float distance = length(u_Light.Position - v_FragmentPosition);
	float attenuation = 1.0f / (u_Light.Constant + u_Light.Linear * distance + u_Light.Quadratic * distance * distance);
	vec3 ambient = vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * u_Light.Ambient;

	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_Light.Position - v_FragmentPosition);
	float diffuseStrength = max(dot(n, l), 0.0f);
	vec3 diffuse = diffuseStrength * vec3(texture(u_Material.AmbientDiffuse, v_TexCoords)) * u_Light.Diffuse;

	vec3 v = normalize(u_CameraPosition - v_FragmentPosition);
	vec3 r = reflect(-l, n);
	float specularStrength = pow(max(dot(v, r), 0.0f), u_Material.Shininess);
	vec3 specular = specularStrength * vec3(texture(u_Material.Specular, v_TexCoords)) * u_Light.Specular;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 color = ambient + diffuse + specular;

	fragColor = vec4(color, 1.0f);
}
