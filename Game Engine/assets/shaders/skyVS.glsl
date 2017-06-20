#version 150

in vec3 vertexPosition;

out vec3 vertexTexCoordsOut;

uniform vec3 cameraPos;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertexTexCoordsOut = vertexPosition;
	gl_Position = (projection*view) * vec4(vertexPosition + cameraPos, 1.0);
}