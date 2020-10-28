#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; //Era aColor per i vertex color
layout (location = 2) in vec2 aTextCoord;

layout (location = 1) uniform mat4 model;
layout (location = 5) uniform mat4 projection;
layout (location = 6) uniform mat4 view;
layout (location = 9) uniform mat3 normalMatrix;

//out vec3 ourColor;
out vec2 textCoord;
out vec3 vertexNormal;
out vec3 fragPosition;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    fragPosition = vec3(view * model * vec4(aPos, 1.0)); //Calcolo la posizione del fragment in world space per passarla al fragment Shader
    //ourColor = aColor;
    textCoord = aTextCoord;
    //vertexNormal = aNormal;
    //vertexNormal = mat3(transpose(inverse(model))) * aNormal;  
    vertexNormal = normalMatrix * aNormal;  

}