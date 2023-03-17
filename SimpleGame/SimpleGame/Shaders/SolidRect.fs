#version 330

layout(location=0) out vec4 FragColor;
// 버텍스 셰이더와 반대로 0 번째에 '출력'을 저장하는 버퍼가 있을 것

uniform vec4 u_Color;
in vec4 Color;

void main()
{
	FragColor = vec4(Color.r, Color.g, Color.b, Color.a);
}
