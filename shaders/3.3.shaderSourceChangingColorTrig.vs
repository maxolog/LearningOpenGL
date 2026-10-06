#version 330 core
layout (location = 0) in vec3 aPos;

uniform float xOffset;

uniform mat4 model1;
uniform mat4 view;
uniform mat4 projection;

void main()
{
gl_Position = projection * view * model1 * vec4(aPos.x + xOffset, -aPos.y + xOffset, aPos.z, 1.0);
}
