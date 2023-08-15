#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

out vec3 v_Normal;

void main()
{
	v_Normal = a_Normal;
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
}

#type fragment
#version 460 core

in vec3 v_Normal;

uniform vec3 u_LampColor;

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(u_LampColor, 1.0f);
}
