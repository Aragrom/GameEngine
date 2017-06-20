#version 150

in vec3 vertexPosition;
in vec3 vertexNormals;

out vec4 vertexColourOut;

uniform mat4 MVP;
uniform mat4 Model;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;

void main()
{
	vec3 worldNorm = normalize(Model*vec4(vertexNormals,0.0f)).xyz;
	float diffuseTerm = dot(worldNorm, lightDirection);
	vertexColourOut = (ambientMaterialColour*ambientLightColour)*(diffuseMaterialColour*diffuseLightColour*diffuseTerm);
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}