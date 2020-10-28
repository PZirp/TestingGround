#version 430 core

//in vec3 ourColor;
in vec2 textCoord; 
in vec3 vertexNormal;
in vec3 fragPosition; 

layout (location = 4) uniform float alpha;
layout (location = 10) uniform vec3 cameraPosition;

struct Material {
    sampler2D diffuseTexture; //11
    sampler2D specularTexture;
    float shininess; //13 Roughness, per modo di dire 12
}; 
  
layout (location = 11) uniform Material material;

struct Light {
    vec3 position; //Posizione eye space della luce 14
  
    vec3 ambient; //Intensità dell'ambient 15	
    vec3 diffuse; //Intensistà della diffuse 16
    vec3 specular; //Specular strenght 17
};

layout (location = 14) uniform Light light;  

out vec4 FragColor;

void main()
{
   
	float ambientStrenght = 0.1f;
	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	vec3 normal = normalize(vertexNormal);
	vec3 lightDirection = normalize(light.position - fragPosition);  
	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

	//float specularStrength = 1.0f; Non serve più, dato che è nella struct
	//vec3 viewDirection = normalize(cameraPosition - fragPosition); //Dato che ora è in view space, non serve più calcolare la distanza tra la camera e il fragment.
	vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);		

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
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
	//vec3 viewDirection = normalize(cameraPosition - fragPosition); //Questo serviva quando calcolavo l'illuminazione in world space, ma dato che ora lo faccio in view space non c'è bisono della posizione della camera, che è sempre a (0.0.0)
	vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);		

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 2048);
	vec3 specular = specularStrength * spec * lightColor;  

	FragColor = vec4(ambient + diffuse + specular, 1.0f) * vec4(1.0f, 0.5f, 0.31f, 1.0f); //mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);  
    //FragColor = vec4(ambient, 1.0f) * mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);
    //FragColor = vec4(ambient, 1.0f) * vec4(vertexNormal, 1.0f);
}
*/