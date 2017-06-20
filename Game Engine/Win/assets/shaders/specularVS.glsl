#version 150

in vec3 vertexPosition;
in vec3 vertexNormals;

out vec4 vertexColourOut;

uniform mat4 MVP;
uniform mat4 Model;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

void main()
{
	
	
	vec3 worldNorm = normalize(Model*vec4(vertexNormals,0.0f)).xyz;
	float diffuseTerm = dot(worldNorm, lightDirection);

	vec3 worldPos = (Model*vec4(vertexPosition, 1.0)).xyz;
	vec3 cameraDirection = normalize(cameraPosition - worldPos);
	vec3 halfWayVec = normalize(cameraDirection + lightDirection);
	float specularTerm = pow(dot(worldNorm, halfWayVec), specularPower);
	
	vertexColourOut = (ambientMaterialColour*ambientLightColour) + (diffuseMaterialColour*diffuseLightColour*diffuseTerm) + (specularMaterialColour*specularLightColour*specularTerm);
	
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}