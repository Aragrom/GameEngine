#version 150

out vec4 FragColor;

in vec4 vertexColourOut;


void main()
{
	//FragColor = vertexColourOut;
	FragColor = vec4(0.3f,0.3f,0.3f,1.0f);
}