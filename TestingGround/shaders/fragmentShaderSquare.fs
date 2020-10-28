#version 430 core

//in vec3 ourColor;
in vec2 textCoord; 
in vec3 vertexNormal;
in vec3 fragPosition; 

//layout (location = 2) uniform sampler2D ourTexture;
//layout (location = 3) uniform sampler2D ourTexture2;
layout (location = 4) uniform float alpha;
//layout (location = 7) uniform vec3 lightColor;
//layout (location = 8) uniform vec3 lightPosition;
layout (location = 10) uniform vec3 cameraPosition;

struct Material {
    //vec3 ambient; //11 Colore dell'ambient light
    //vec3 diffuse; //12 Colore della luce che colpisce
	sampler2D diffuseTexture; //11
    //vec3 specular; //12 Colore del riflesso insomma 11
	sampler2D specularTexture;
    float shininess; //13 Roughness, per modo di dire 12
}; 
  
layout (location = 11) uniform Material material;

struct Light {
    vec3 position; //Posizione
  
    vec3 ambient; //Intensità dell'ambient
    vec3 diffuse; //Intensistà della diffuse
    vec3 specular; //Specular power
};

layout (location = 14) uniform Light light;  

out vec4 FragColor;

void main()
{
   
	float ambientStrenght = 0.1f;
	//vec3 ambient = lightColor * material.ambient;
	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	vec3 normal = normalize(vertexNormal);
	vec3 lightDirection = normalize(light.position - fragPosition);  
	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	//vec3 diffuse = lightColor * (diffuseAmount * material.diffuse); 
	vec3 diffuse = light.diffuse * (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

	//float specularStrength = 1.0f;
	//vec3 viewDirection = normalize(cameraPosition - fragPosition);
	vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);		

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	//vec3 specular = spec * (lightColor * material.specular);   
	vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   


	FragColor = vec4(ambient + diffuse + specular, 1.0f); //* vec4(1.0f, 0.5f, 0.31f, 1.0f); //mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);  
    //FragColor = vec4(ambient, 1.0f) * mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);
    //FragColor = vec4(ambient, 1.0f) * vec4(vertexNormal, 1.0f);
}


/*void main()
{
   
	float ambientStrenght = 0.1f;
	vec3 ambient = lightColor * ambientStrenght;

	vec3 normal = normalize(vertexNormal);
	vec3 lightDirection = normalize(lightPosition - fragPosition);  
	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = diffuseAmount * lightColor;

	float specularStrength = 1.0f;
	//vec3 viewDirection = normalize(cameraPosition - fragPosition);
	vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);		

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 2048);
	vec3 specular = specularStrength * spec * lightColor;  

	FragColor = vec4(ambient + diffuse + specular, 1.0f) * vec4(1.0f, 0.5f, 0.31f, 1.0f); //mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);  
    //FragColor = vec4(ambient, 1.0f) * mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);
    //FragColor = vec4(ambient, 1.0f) * vec4(vertexNormal, 1.0f);
}
*/