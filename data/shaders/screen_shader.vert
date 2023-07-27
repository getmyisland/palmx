#version 330 core

layout (location = 0) in vec3 position;

out vec2 texCoords;

void main()
{
	gl_Position = vec4(position, 1.0);

	// Map the vertex position from the range [-1, 1] to the range [0, 1]
    texCoords = (position.xy + 1.0) * 0.5;
}