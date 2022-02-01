#version 430 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_texcoord;

layout(location = 0) uniform mat4 proj_view;

out vec2 texcoord;
void main()
{
    gl_Position = proj_view * vec4(v_position, 1.0);
    texcoord = v_texcoord;
}
