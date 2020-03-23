#version 420

uniform vec4 lightPos;

// colour info
uniform vec4 objectColour;
uniform vec3 lightAmbient;
uniform vec3 lightDiffuse;
uniform vec3 lightSpecular;

//scalars
uniform float lightSpecularExponenet;
uniform float attenuationConstant;
uniform float attenuationLinear;
uniform float attenuationQuadratic;

in vec3 position;
in vec3 normal;

out vec4 outColour;


void main()
{
	outColour.rgb = lightAmbient;

	//account for rasterizer interpolating
	vec3 norm = normalize(normal);

	vec3 lightVec = lightPos.xyz - position;
	float dist = length(lightVec);
	vec3 lightDir = lightVec/dist;

	float NdotL = dot(normal,lightDir);

	if(NdotL > 0.0)
	{
		// the light contributes to this surface

		// calcualte the attenuation(falloff)
		float attenuation = 1.0/(attenuationConstant + (attenuationLinear*dist) + (attenuationQuadratic * dist * dist));

		//calculate the diffuse contribution
		outColour.rgb += lightDiffuse * NdotL * attenuation;

		vec3 halfVector = normalize(lightDir + normalize(-position));
		float NdotHV = max(dot(normal,halfVector),0.0);

		// calculate the specular contribution
		outColour.rgb += lightSpecular * pow(NdotHV,lightSpecularExponenet) * attenuation;

	}

	outColour.rgb *= objectColour.rgb;
	outColour.a = objectColour.a;
}