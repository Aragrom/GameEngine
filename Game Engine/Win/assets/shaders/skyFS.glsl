#version 150

out vec4 FragColor;
in vec3 vertexTexCoordsOut;

uniform samplerCube cubeTexture;

void main()
{
	FragColor = texture(cubeTexture, vertexTexCoordsOut);
	//FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
}