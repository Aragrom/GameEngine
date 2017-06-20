#version 150

out vec4 FragColor;
in vec2 textureCoords;

uniform sampler2D texture0;

uniform mat3 colourFilter = mat3(.393, .769, .189,
	.349, .686, .168,
	.272, .534, .131);

vec2 boxFilter[4] = vec2[4]( vec2(0.0002f, 0.002f), vec2(-0.002f, 0.002f),vec2(0.002f,-0.002f),vec2(-0.002f,-0.002f) );

void main()
{
	vec3 colour = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 4; i++)
	{
		colour += texture(texture0, textureCoords + boxFilter[i]).xyz;
	}
	colour = colour*colourFilter;
	FragColor = vec4(colour, 1.0);
}