#version 330 core
layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    TexCoords = vec2(aTexCoords.x, aTexCoords.y);
	gl_Position = projection * view * model * vec4(vertex, 1.0);
}