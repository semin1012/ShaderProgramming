#version 330

layout(location=0) out vec4 FragColor;

varying vec4 v_Color;	// in vecter4 vertex

void main()
{
	FragColor = v_Color;
}
