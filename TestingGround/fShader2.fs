#version 430 core

out vec4 FragColor;

layout (location = 2) uniform vec4 ourColor;

void main()
{
   FragColor = ourColor; //vec4(0.0f, 1.0f, 1.0f, 1.0f);
}