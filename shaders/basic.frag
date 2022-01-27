#version 330 core

in vec2 f_texcoord;
uniform sampler2D atlas;
out vec4 FragColor;

void main()
{
	FragColor = texture(atlas, f_texcoord);
}