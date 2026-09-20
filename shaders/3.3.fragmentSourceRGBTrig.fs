#version 330 core

out vec4 FragColor;

in vec2 TexCoord;
in vec3 ourColor;

uniform sampler2D seriiTexture;
uniform sampler2D likeFace;

void main()
{
   FragColor = mix(
      texture(seriiTexture, TexCoord), 
      texture(likeFace, TexCoord), 
      0.2);
}