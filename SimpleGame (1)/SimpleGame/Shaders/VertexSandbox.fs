#version 330

layout(location=0) out vec4 FragColor;

in float v_Alpha;

void main()
{
	float newLines = sin(100.0*(1.0 - v_Alpha));
	FragColor = vec4(1.0, 1.0, 1.0, newLines);
}
