#version 430 core

in vec3 f_position;
//in vec3 f_normal;
//in vec2 f_texcoord;

out vec4 frag_color;

//uniform sampler2D texture_img;

void main()
{
	//vec3 light = vec3(16, 48, 16);
	//vec3 lightDir = normalize(light - f_position);
	//float diff = max(dot(f_normal, lightDir), 0.0);
	//float ambient = 0.3;
	//vec3 lightColor = vec3(1, 1, 1);
	//vec3 diffuse = (diff + ambient) * lightColor;
	//vec3 color = vec3(0.4, 7.0, 0.5);
	//FragColor = vec4(ambient + diffuse, 1.0) * texture(texture_img, f_texcoord);
	frag_color = vec4(1.0, 0.5, 0.3, 1.0);
}
