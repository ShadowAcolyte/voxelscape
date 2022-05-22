#version 430 core

layout (location = 0) in vec3 v_position;
//layout (location = 1) in vec3 v_normal;
//layout (location = 2) in vec2 v_texcoord;

layout(location = 0) uniform mat4 proj_view;

out vec3 f_position;
//out vec3 f_normal;
//out vec2 f_texcoord;

void main()
{
    gl_Position = proj_view * vec4(v_position, 1.0);
    f_position = v_position;
    //f_normal = v_normal;
    //f_texcoord = v_texcoord;
}
