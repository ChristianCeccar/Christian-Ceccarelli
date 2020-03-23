#version 420
// Moishe Grosh 100615969
#define NUM_POINT_LIGHTS 3

#define UP_COLOUR vec3(0,0,1)
#define DOWN_COLOUR vec3(1,0,0)
#define LEFT_COLOUR vec3(1,0,1)
#define RIGHT_COLOUR vec3(0,1,0)
#define FRONT_COLOUR vec3(0,1,1)
#define BACK_COLOUR vec3(1,1,0)



struct PointLight
{
	vec4 position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	float SpecularExponent;	

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

};


struct DirectionalLight
{
	vec4 direction;

	float SpecularExponent;	

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

};

uniform PointLight pointLights[NUM_POINT_LIGHTS];

uniform DirectionalLight directionalLight;

in vec3 position;
in vec2 texCoord;
in vec3 normal;
in vec3 modelNormal;

out vec4 outColour;

vec3 calculatePointLight(PointLight light, vec3 norm);

vec3 calculateDirectionalight(DirectionalLight light, vec3 norm);

void main()
{
	

	//account for rasterizer interpolating
	vec3 norm = normalize(normal);

	outColour.rgb = calculateDirectionalight(directionalLight,norm);
	
	for (int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		outColour.rgb += calculatePointLight(pointLights[i],norm);
	}
	
	vec3 colour = max(modelNormal.x,0.0) * RIGHT_COLOUR + max(-modelNormal.x,0.0) * LEFT_COLOUR + 
				max(modelNormal.y , 0.0) * UP_COLOUR + max(-modelNormal.y,0.0) * DOWN_COLOUR +
				max(modelNormal.z,0.0) * FRONT_COLOUR + max(-modelNormal.z ,0.0) * BACK_COLOUR;

	outColour.rgb *= colour;
	outColour.a = 1;
}

vec3 calculatePointLight(PointLight light, vec3 norm)
{
	vec3 lightVec = light.position.xyz - position;
	float dist = length(lightVec);
	vec3 lightDir = lightVec/dist;



		// calcualte the attenuation(falloff)
		float attenuation = 1.0/(light.constantAttenuation + (light.linearAttenuation*dist) + (light.quadraticAttenuation * dist * dist));

		// Ambient 
		vec3 Ambient = attenuation * light.Ambient;

		// Diffuse 
		float NdotL = max(dot(norm,lightDir),0.0);
		vec3 diffuse = light.Diffuse * NdotL * attenuation;
		
		// Specular
		vec3 reflectDir = reflect( -lightDir,norm);
		float VdotR = max(dot(normalize(-position),reflectDir),0.0);
		vec3 Specular = pow(VdotR, light.SpecularExponent) * attenuation * light.Specular;


		return Ambient + diffuse + Specular;
		
}

vec3 calculateDirectionalight(DirectionalLight light, vec3 norm)
{

	vec3 lightDir = normalize(-light.direction).xyz;





		// Ambient 
		vec3 Ambient = light.Ambient;

		// Diffuse 
		float NdotL = max(dot(norm,lightDir),0.0);
		vec3 diffuse = light.Diffuse * NdotL;
		
		// Specular
		vec3 reflectDir = reflect( -lightDir,norm);
		float VdotR = max(dot(normalize(-position),reflectDir),0.0);
		vec3 Specular = pow(VdotR, light.SpecularExponent) * light.Specular;


		return Ambient + diffuse + Specular;

		

}