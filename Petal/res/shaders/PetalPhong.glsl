#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;
uniform mat3 u_NormalMatrix;

out vec3 v_Normal;
out vec3 v_FragmentPosition;

void main()
{
	v_Normal = u_NormalMatrix * a_Normal;
	v_FragmentPosition = vec3(u_Model * vec4(a_Position, 1.0f));
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
}

#type fragment
#version 460 core

struct Material
{
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
};

struct Light
{
	vec3 Position;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
};

in vec3 v_Normal;
in vec3 v_FragmentPosition;

uniform Material u_Material;
uniform Light u_Light;
uniform vec3 u_CameraPosition;

layout (location = 0) out vec4 fragColor;

void main()
{
	vec3 ambient = u_Material.Ambient * u_Light.Ambient;

	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_Light.Position - v_FragmentPosition);
	float diffuseStrength = max(dot(n, l), 0.0f);
	vec3 diffuse = diffuseStrength * u_Material.Diffuse * u_Light.Diffuse;

	vec3 v = normalize(u_CameraPosition - v_FragmentPosition);
	vec3 r = reflect(-l, n);
	float specularStrength = pow(max(dot(v, r), 0.0f), u_Material.Shininess);
	vec3 specular = specularStrength * u_Material.Specular * u_Light.Specular;

	vec3 color = ambient + diffuse + specular;

	fragColor = vec4(color, 1.0f);
}