#version 430 core

/* face data: packed into 32 bit unsigned int
   going from least significant bit to most:
   bits 1-3   -> face direction (north = 1, followed by south, east, west, top, bottom = 6
   bits 3-12  -> face position, relative to chunk. 4 bits(0-15) for each axis(x, y and z)
   bits 16-25 -> block id, to resolve texture coords for each block type */
layout(std430, binding = 1) buffer FaceData
{
    uint faces[];
};

layout(std430, binding = 3) buffer Tables
{
	vec4 FACE_VERTEX_TABLE[7][6];
};

layout(location = 0) uniform mat4 proj_view;

out vec2 texcoords;

void main()
{
	uint face_idx = gl_VertexID / 6;
	uint face_vertex_idx = gl_VertexID % 6;

	uint face = faces[face_idx];
	uint direction = face & 0x7;

	vec3 block_pos;
	block_pos.x = (face >> 11) & 0xF;
	block_pos.y = (face >> 7)  & 0xF;
	block_pos.z = (face >> 3)  & 0xF;
	vec3 vert_pos = FACE_VERTEX_TABLE[direction][face_vertex_idx].xyz;

	gl_Position = proj_view * vec4(block_pos + vert_pos, 1.0);

	if (face_vertex_idx == 0)
		texcoords = vec2(0, 0);
	else if (face_vertex_idx == 1)
		texcoords = vec2(0, 1);
	else if (face_vertex_idx == 2)
		texcoords = vec2(1, 1);
	else if (face_vertex_idx == 3)
		texcoords = vec2(1, 1);
	else if (face_vertex_idx == 4)
		texcoords = vec2(1, 0);
	else if (face_vertex_idx == 5)
		texcoords = vec2(0, 0);
}
