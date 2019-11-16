#version 460 core

layout(location = 0) out vec4 color;

//in vec2 v_TexCoord;

//uniform vec4 u_Color;
uniform sampler2D texture1;

void main() {
	color = texture(texture1, v_TexCoord * 10.0) * u_Color;
}