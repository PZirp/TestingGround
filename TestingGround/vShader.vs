#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

layout (location = 0) uniform float offSet;

out vec3 ourColor;
out vec2 textCoord;
void main()
{
   gl_Position = vec4(aPos.x+offSet, aPos.y, aPos.z, 1.0);
   ourColor = aColor;
   textCoord = aTextCoord;
   
}