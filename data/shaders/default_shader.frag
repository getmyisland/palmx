#version 330 core

in vec3 color;
in vec2 texCoord;

out vec4 FragColor;  
  
uniform sampler2D texture_albedo;
uniform sampler2D texture_normal;

void main()
{
    FragColor = texture(texture_albedo, texCoord);
}