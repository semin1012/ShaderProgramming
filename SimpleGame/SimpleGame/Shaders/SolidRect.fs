#version 330

layout(location=0) out vec4 FragColor;
// ���ؽ� ���̴��� �ݴ�� 0 ��°�� '���'�� �����ϴ� ���۰� ���� ��

uniform vec4 u_Color;
in vec4 Color;

void main()
{
	FragColor = vec4(Color.r, Color.g, Color.b, Color.a);
}
