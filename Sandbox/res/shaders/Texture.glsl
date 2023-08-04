#type vertex
#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;

uniform mat4 u_ViewProj;
uniform mat4 u_Model;

out vec2 v_TexCoords;

void main()
{
	v_TexCoords = a_TexCoords;
	gl_Position = u_ViewProj * u_Model * vec4(a_Position, 1.0f);
}

#type fragment
#version 460 core

layout (location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoords);
}
