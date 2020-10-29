#version 430 core

//in vec3 ourColor;
in vec2 textCoord; 
in vec3 vertexNormal;
in vec3 fragPosition; 

//layout (location = 12) uniform float alpha;

struct Material {
    sampler2D diffuseTexture; //4
    sampler2D specularTexture; //5
    float shininess; //6 Roughness, per modo di dire 12
}; 
  
layout (location = 4) uniform Material material;

struct DirectionalLight {
    vec3 direction; //Posizione eye space della luce 7
  
    vec3 ambient; //Intensità dell'ambient 8
    vec3 diffuse; //Intensistà della diffuse 9
    vec3 specular; //Specular strenght 10
};	

layout (location = 7) uniform DirectionalLight directionalLight;  

struct PointLight {
    vec3 position; //Posizione eye space della luce 11
  
    vec3 ambient; //Intensità dell'ambient 12
    vec3 diffuse; //Intensistà della diffuse 13
    vec3 specular; //Specular strenght 14
	
    float constant; //15
    float linear; //16 
    float quadratic; //17
};

layout (location = 11) uniform PointLight pointLight;  

struct SpotLight {
    vec3 position; //Posizione eye space della luce 18
	vec3 direction; //19
	float cutOff; //20
	float outerCutOff; //21

    vec3 ambient; //Intensità dell'ambient 22
    vec3 diffuse; //Intensistà della diffuse 23
    vec3 specular; //Specular strenght 24
	
    float constant; //25
    float linear; //26
    float quadratic; //27
};
layout (location = 18) uniform SpotLight spotLight;  

struct DumbLight {
    vec3 position; //Posizione eye space della luce 7
  
    vec3 ambient; //Intensità dell'ambient 8
    vec3 diffuse; //Intensistà della diffuse 9
    vec3 specular; //Specular strenght 10
};	

layout (location = 28) uniform DumbLight dumbLight;  


out vec4 FragColor;

vec3 ComputeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 ComputePointLight(PointLight light, vec3 normal, vec3 viewDirection);
vec3 ComputeSpotLight(SpotLight light, vec3 normal, vec3 viewDirection);
vec3 ComputeDumbLight(DumbLight light, vec3 normal, vec3 viewDirection);

void main()
{   
	vec3 normal = normalize(vertexNormal);
	vec3 viewDirection = normalize(-fragPosition);
	FragColor = vec4(ComputeSpotLight(spotLight, normal, viewDirection), 1.0f);
    	
	/*vec3 lightDirection = normalize(light.position - fragPosition);  
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    

	//if(theta > light.cutOff) 
	//{       
		float distance    = length(light.position - fragPosition);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

		vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

		float diffuseAmount = max(dot(normal, lightDirection), 0.0);
		vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

		//float specularStrength = 1.0f; Non serve più, dato che è nella struct
		//vec3 viewDirection = normalize(cameraPosition - fragPosition); //Dato che ora è in view space, non serve più calcolare la distanza tra la camera e il fragment.
		vec3 reflectDirection = reflect(-lightDirection, normal);		

		float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
		vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   
		
		ambient = ambient * attenuation;
		diffuse = diffuse * intensity * attenuation;
		specular = specular * intensity * attenuation;
		FragColor = vec4(ambient + (diffuse) + (specular), 1.0f);*/
		//FragColor = vec4(ComputeDumbLight(light, normal, viewDirection), 1.0f);
	//} else {
		//vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));
		//FragColor = vec4(ambient, 1.0f);
	//}

	//FragColor = vec4(ComputePointLight(plight, normal, viewDirection), 1.0f); 
	//FragColor = vec4(ambient + diffuse + specular, 1.0f); //* vec4(1.0f, 0.5f, 0.31f, 1.0f); //mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);  
    //FragColor = vec4(ambient, 1.0f) * mix(texture(ourTexture, textCoord), texture(ourTexture2, textCoord), vec4(texture(ourTexture2, textCoord)).a * alpha);
    //FragColor = vec4(ambient, 1.0f) * vec4(vertexNormal, 1.0f);
}

vec3 ComputeDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection) {
	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	vec3 lightDirection = normalize(-light.direction);  	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 
	
	vec3 reflectDirection = reflect(-lightDirection, normal);		
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   

	return ambient + diffuse + specular;
}

vec3 ComputePointLight(PointLight light, vec3 normal, vec3 viewDirection) {	
	float distance    = length(light.position - fragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	vec3 lightDirection = normalize(light.position - fragPosition);  	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

	vec3 reflectDirection = reflect(-lightDirection, normal);		
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   

	return (ambient * attenuation) + (diffuse * attenuation) + (specular * attenuation);
}

vec3 ComputeSpotLight(SpotLight light, vec3 normal, vec3 viewDirection) {	
	vec3 lightDirection = normalize(light.position - fragPosition);  
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);    

	//if(theta > light.cutOff) 
	//{       
	float distance    = length(light.position - fragPosition);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

	vec3 reflectDirection = reflect(-lightDirection, normal);		
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   
		
	ambient = ambient * attenuation;
	diffuse = diffuse * intensity * attenuation;
	specular = specular * intensity * attenuation;
	return ambient + diffuse + specular;
}


vec3 ComputeDumbLight(DumbLight light, vec3 normal, vec3 viewDirection) {
	//float ambientStrenght = 0.1f;
	vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, textCoord));

	//vec3 normal = normalize(vertexNormal);
	vec3 lightDirection = normalize(light.position - fragPosition);  
	
	float diffuseAmount = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = (light.diffuse)* (diffuseAmount * vec3(texture(material.diffuseTexture, textCoord))); 

	//float specularStrength = 1.0f; Non serve più, dato che è nella struct
	//vec3 viewDirection = normalize(cameraPosition - fragPosition); //Dato che ora è in view space, non serve più calcolare la distanza tra la camera e il fragment.
	//vec3 viewDirection = normalize(-fragPosition);
	vec3 reflectDirection = reflect(-lightDirection, normal);		

	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * vec3(texture(material.specularTexture, textCoord)));   

	return ambient + diffuse + specular;
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