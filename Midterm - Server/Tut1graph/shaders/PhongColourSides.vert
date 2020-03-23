#version 420
// Moishe Grosh 100615969
uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProj;

layout(location = 0) in vec3 in_Vert;
layout(location = 1) in vec2 in_UV;
layout(location = 2) in vec3 in_Normal;

out vec3 position;
out vec2 texCoord;
out vec3 normal;
out vec3 modelNormal;

void main()
{
	modelNormal = in_Normal;
	texCoord = in_UV;
	normal = mat3(uView) * mat3(uModel) * in_Normal;

	vec4 viewSpacePos = uView * uModel * vec4(in_Vert,1.0f);
	position = viewSpacePos.xyz;
	
	gl_Position = uProj * viewSpacePos;


}