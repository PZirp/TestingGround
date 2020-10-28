#version 430 core
out vec4 FragColor;

layout (location = 3) uniform vec3 lightCubeColor;

void main()
{
    FragColor = vec4(lightCubeColor, 1.0f); //vec4(1.0); // set all 4 vector values to 1.0
}