#version 330 core

in vec2 texCoords;

out vec4 fragColor;

uniform sampler2D renderTexture;

void main()
{
	// Fetch the color from the texture using the texture coordinates
    vec4 texColor = texture(renderTexture, texCoords);
    
    // Output the fetched color
    fragColor = texColor;
}