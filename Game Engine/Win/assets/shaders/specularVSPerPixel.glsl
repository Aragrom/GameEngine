#version 150

in vec3 vertexPosition;
in vec3 vertexNormals;

out vec3 vertexNormalOut;
out vec3 cameraDirectionOut;

uniform mat4 MVP;
uniform mat4 Model;


uniform vec3 cameraPosition;

void main()
{
	vertexNormalOut = normalize(Model*vec4(vertexNormals, 0.0f)).xyz;
	vec3 worldPos = (Model*vec4(vertexPosition, 1.0)).xyz;
	cameraDirectionOut = normalize(cameraPosition - worldPos);
	
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}