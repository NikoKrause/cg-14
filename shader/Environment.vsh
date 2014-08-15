#version 330 core

layout(location = 0) in vec3 i_windowpos;
layout(location = 1) in vec2 i_coord;

uniform float u_light;
uniform mat4 u_transform;

out VertexData
{

	vec3 coord;

} outData;

void main()
{

	gl_Position = u_transform * vec4(i_windowpos , 1);

	outData.coord = i_windowpos;

}