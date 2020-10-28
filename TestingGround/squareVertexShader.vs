#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

layout (location = 0) uniform float offSet;
layout (location = 1) uniform mat4 transform;
layout (location = 5) uniform mat4 projection;
layout (location = 6) uniform mat4 view;

out vec3 ourColor;
out vec2 textCoord;
void main()
{
   vec4 loc = vec4(aPos, 1.0);
   loc = vec4(loc.x+offSet, loc.y, loc.z, 1.0);
   gl_Position = loc;
   ourColor = aColor;
   textCoord = aTextCoord;
   
}