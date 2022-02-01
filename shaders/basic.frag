#version 430 core

in vec2 texcoord;
out vec4 FragColor;

uniform sampler2D texture_img;

void main()
{
	//FragColor = vec4(0.0, 1.0, 0.5, 1.0);
	FragColor = texture(texture_img, texcoord);
}
