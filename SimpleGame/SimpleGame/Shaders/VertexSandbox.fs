#version 330

layout(location=0) out vec4 FragColor;

in float v_Alpha;

void main()
{
	float newLines = sin(50 * (1.0 - v_Alpha));
	// float newLines = int(50 * (1.0 - v_Alpha)) % 2.0;
	// other way
	FragColor = vec4(1.0, 1.0, 1.0, newLines);
}
