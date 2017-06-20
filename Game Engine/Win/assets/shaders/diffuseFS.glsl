#version 150

out vec4 FragColor;

in vec4 vertexColourOut;


void main()
{
	FragColor = vertexColourOut;
}