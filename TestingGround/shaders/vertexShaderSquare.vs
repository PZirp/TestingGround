#version 430 core

//Vertex attribute

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; //Era aColor per i vertex color
layout (location = 2) in vec2 aTextCoord;

// Uniforms

layout (location = 0) uniform mat4 model;
layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 view;
layout (location = 3) uniform mat3 normalMatrix;

//out vec3 ourColor;
out vec2 textCoord;
out vec3 vertexNormal;
out vec3 fragPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragPosition = vec3(view * model * vec4(aPos, 1.0)); //Calcolo la posizione del fragment in view space space per passarla al fragment Shader
    //ourColor = aColor;
    textCoord = aTextCoord;
    vertexNormal = normalMatrix * aNormal;  

}