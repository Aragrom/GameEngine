#version 150

out vec4 FragColor;
in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 texCoordsOut;

uniform vec3 lightDirection;

uniform vec4 ambientMaterialColour;
uniform vec4 diffuseMaterialColour;
uniform vec4 specularMaterialColour;
uniform float specularPower;

uniform vec4 ambientLightColour;
uniform vec4 diffuseLightColour;
uniform vec4 specularLightColour;

uniform sampler2D diffuseMap;
uniform sampler2D specMap;

void main()
{
	float diffuseTerm = dot(vertexNormalOut, lightDirection);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDirection);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);

	vec4 diffuseTextureColour = texture(diffuseMap, texCoordsOut);
	vec4 specTextureColour = texture(specMap, texCoordsOut);

	FragColor = (ambientMaterialColour*ambientLightColour) + ((diffuseMaterialColour + diffuseTextureColour)*diffuseLightColour*diffuseTerm) + 
		((specularMaterialColour + specTextureColour)*specularLightColour*specularTerm);
}