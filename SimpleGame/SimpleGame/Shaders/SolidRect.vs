#version 330

in vec3 a_Position;	// in �̶� ����� �̰��� ATTRIBUTE (VS INPUT)
// �ᱹ �ε����� �˾ƾ� �Ѵٴ� ���ε�, 0���� 1���� ��� �ƴ°�. �ڵ����� ������.
// 0�� ������ ������ �ڵ���. �׷��� layout(location = 0) �̶� �ϸ� 0���� �����̼��� ������ ��. ����.
in vec3 a_Position1;
// layout(location = 1) ���� �ڵ带 �� �ᵵ �Ǳ� �ѵ�, �׷� 0������ 1������ ����� ���� ��� �ڵ� ��������.
// layout �� ������ glGetAttribLocation �ڵ带 ���.
uniform vec4 u_Trans;

void main()
{
	vec4 newPosition;
	newPosition.xy = (a_Position.xy + a_Position1.xy ) *u_Trans.w + u_Trans.xy;
	newPosition.z = 0;
	newPosition.w= 1;
	gl_Position = newPosition;
}
