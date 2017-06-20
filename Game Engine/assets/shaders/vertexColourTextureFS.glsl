#version 150

out vec4 FragColor;
in vec2 vertexTexCoordsOut;
in vec4 vertexColourOut;

uniform sampler2D texture0;

void main()
{
	FragColor = texture(texture0, vertexTexCoordsOut)*vertexColourOut;
}