#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

void main()
{
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
}

#type fragment
#version 460 core

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;

layout (location = 0) out vec4 color;

void main()
{
	color = vec4(u_ObjectColor * u_LightColor, 1.0f);
}
