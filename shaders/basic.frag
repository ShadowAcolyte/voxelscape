#version 430 core

//in vec2 f_texcoord;
//uniform sampler2D atlas;
out vec4 FragColor;

void main()
{
	//FragColor = texture(atlas, f_texcoord);
	FragColor = vec4(0.0, 1.0, 0.5, 1.0);
}
