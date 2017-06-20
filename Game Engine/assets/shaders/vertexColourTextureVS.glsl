#version 150

in vec3 vertexPosition;
in vec2 vertexTexCoords;
in vec4 vertexColour;

out vec4 vertexColourOut;
out vec2 vertexTexCoordsOut;
uniform mat4 MVP;

void main()
{
	vertexTexCoordsOut = vertexTexCoords;
	vertexColourOut = vertexColour;
	gl_Position = MVP * vec4(vertexPosition, 1.0);
}