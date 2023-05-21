#version 330 core
in vec3 color;
in vec2 texCoord;

out vec4 FragColor;  
  
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_normal1;

void main()
{
    FragColor = texture(texture_diffuse1, texCoord);
}