#version 150

in vec3 vertexPosition;
in vec3 vertexNormals;
in vec2 vertexTexCoords;
in vec3 vertexTangents;
in vec3 vertexBinormals;

out vec3 vertexNormalOut;
out vec3 cameraDirectionOut;
out vec3 lightDirectionOut;
out vec2 texCoordsOut;

uniform mat4 MVP;
uniform mat4 Model;

uniform vec3 lightDirection;
uniform vec3 cameraPosition;

void main()
{
	mat3 tangentMatrix = mat3(normalize(vertexNormals), normalize(vertexTangents), normalize(vertexBinormals));

	vec3 vertexNormalModel = normalize(Model*vec4(vertexNormals, 0.0f)).xyz;
	vec3 worldPos = (Model*vec4(vertexPosition, 1.0)).xyz;
	vec3 cameraDir = normalize(cameraPosition - worldPos);

	//lightDirectionOut = lightDirection;
	//vertexNormalOut = vertexNormalModel;
	//cameraDirectionOut = cameraDir;

	lightDirectionOut = normalize(tangentMatrix*lightDirection);
	vertexNormalOut = normalize(tangentMatrix*vertexNormalModel);
	cameraDirectionOut = normalize(tangentMatrix*cameraDir);

	texCoordsOut = vertexTexCoords;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}