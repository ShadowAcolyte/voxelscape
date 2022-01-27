#version 330 core

layout (location = 0) in vec3 aPos;
out vec2 f_texcoord;

uniform mat4 proj_view;

void main()
{
    gl_Position = proj_view *  vec4(aPos.x, aPos.y, aPos.z, 1.0);
    f_texcoord = aPos.xy;
}