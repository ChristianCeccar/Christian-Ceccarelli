#version 420
// Moishe Grosh 100615969
#define NUM_POINT_LIGHTS 3

struct PointLight
{
	vec4 position;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

	

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

};

struct DirectionalLight
{
	vec4 direction;

	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;

};
struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
	vec3 hue;



	float SpecularExponent;	
};

uniform PointLight pointLights[NUM_POINT_LIGHTS];

uniform DirectionalLight directionalLight;

uniform Material material;

in vec3 position;
in vec2 texCoord;
in vec3 normal;

out vec4 outColour;

vec3 calculatePointLight(PointLight light, vec3 norm, vec4 materialDiffuse, vec4 materialSpecular);

vec3 calculateDirectionalLight(DirectionalLight, vec3 norm, vec4 materialDiffuse, vec4 materialSpecular);

void main()
{
	//the following code converting the normals from tanget space to world space 
	vec3 posDx = dFdx(position);
	vec3 posDy = dFdy(position);

	vec2 textDx = dFdx(texCoord);
	vec2 textDy = dFdx(texCoord);

	
	vec3 tanget = normalize(textDy.y * posDx - textDx.y * posDy);
	vec3 binorm = normalize(textDy.x * posDx - textDx.x * posDy);

	vec3 n = normalize(normal);

	vec3 x = cross(n, tanget);

	tanget = normalize(cross(x,n));

	x = cross(binorm, n);

	binorm = normalize(cross(n,x));

	mat3 tangetSpace = mat3(tanget, binorm, n);
	//end of tanget space code

	vec3 norm = normalize(tangetSpace * (2.0 * texture(material.normal, texCoord).rgb - vec3(1)));

	//account for rasterizer interpolating
	vec4 diffuse = texture(material.diffuse,texCoord);
	vec4 specular = texture(material.specular,texCoord);

	outColour.rgb = calculateDirectionalLight(directionalLight,norm,diffuse,specular);
	
	for (int i = 0; i < NUM_POINT_LIGHTS; i++)
	{
		outColour.rgb += calculatePointLight(pointLights[i],norm,diffuse,specular);
	}
	
	outColour.rgb *= material.hue;
	outColour.a = diffuse.a;
}

vec3 calculatePointLight(PointLight light, vec3 norm, vec4 materialDiffuse, vec4 materialSpecular)
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
		vec3 diffuse = light.Diffuse * NdotL * attenuation * materialDiffuse.rgb;
		
		// Specular
		vec3 reflectDir = reflect( -lightDir,norm);
		float VdotR = max(dot(normalize(-position),reflectDir),0.0);
		vec3 Specular = light.Specular * pow(VdotR, material.SpecularExponent) * attenuation * materialSpecular.rgb;


		return Ambient + diffuse + Specular;
		
}
vec3 calculateDirectionalLight(DirectionalLight light, vec3 norm, vec4 materialDiffuse, vec4 materialSpecular)
{

	vec3 lightDir = normalize(-light.direction).xyz;


		// Ambient 
		vec3 Ambient = light.Ambient;

		// Diffuse 
		float NdotL = max(dot(norm,lightDir),0.0);
		vec3 diffuse = light.Diffuse * NdotL * materialDiffuse.rgb;
		
		// Specular
		vec3 reflectDir = reflect( -lightDir,norm);
		float VdotR = max(dot(normalize(-position),reflectDir),0.0);
		vec3 Specular = light.Specular * pow(VdotR, material.SpecularExponent) * materialSpecular.rgb;


		return Ambient + diffuse + Specular;
		

}