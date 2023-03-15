#version 330

layout(location = 0) in vec3 a_Position;	// in �̶� ����� �̰��� ATTRIBUTE (VS INPUT)
// �ᱹ �ε����� �˾ƾ� �Ѵٴ� ���ε�, 0���� 1���� ��� �ƴ°�. �ڵ����� ������.
// 0�� ������ ������ �ڵ���. �׷��� layout(location = 0) �̶� �ϸ� 0���� �����̼��� ������ ��. ����.

uniform vec4 u_Trans;
//
layout(location = 0) in vec3 b_Position;	// in �̶� ����� �̰��� ATTRIBUTE (VS INPUT)
//
uniform vec4 u_Trans2;
//

void main()
{
	vec4 newPosition;
	newPosition.xy = a_Position.xy*u_Trans.w + u_Trans.xy;
	newPosition.z = 0;
	newPosition.w= 1;
	gl_Position = newPosition;
	//
	vec4 newPosition2;
	newPosition2.xy = b_Position.xy*u_Trans2.w + u_Trans2.xy;
	newPosition2.z = 0;
	newPosition2.w= 1;
	gl_Position = newPosition2;
}
