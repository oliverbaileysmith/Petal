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

in vec3 v_Normal;
in vec3 v_FragmentPosition;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_CameraPosition;

layout (location = 0) out vec4 fragColor;

void main()
{
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * u_LightColor;

	vec3 n = normalize(v_Normal);
	vec3 l = normalize(u_LightPosition - v_FragmentPosition);
	float diffuseStrength = max(dot(n, l), 0.0f);
	vec3 diffuse = diffuseStrength * u_LightColor;

	vec3 v = normalize(u_CameraPosition - v_FragmentPosition);
	vec3 r = reflect(-l, n);
	float specularStrength = 0.5f;
	vec3 specular = specularStrength * pow(max(dot(v, r), 0.0f), 16.0f) * u_LightColor;

	vec3 color = (ambient + diffuse + specular) * u_ObjectColor;

	fragColor = vec4(color, 1.0f);
}
