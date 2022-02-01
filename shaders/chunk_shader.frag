#version 430 core

in vec2 texcoords;
out vec4 frag_color;

uniform sampler2D texture_img;

void main()
{
	//frag_color = vec4(0.0, 1.0, 0.5, 1.0);
	frag_color = texture(texture_img, texcoords / 16.0f);
}
