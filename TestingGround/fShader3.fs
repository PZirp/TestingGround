#version 430 core

in vec3 ourColor;
in vec2 textCoord; 

layout (location = 2) uniform sampler2D ourTexture;
layout (location = 3) uniform sampler2D ourTexture2;
layout (location = 4) uniform float alpha;

out vec4 FragColor;

void main()
{
   //FragColor = vec4(ourColor, 1.0f);
   //FragColor = texture(ourTexture, textCoord);
   
   FragColor = mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);
}
