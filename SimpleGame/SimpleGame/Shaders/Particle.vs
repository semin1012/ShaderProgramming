#version 330

in vec3 a_Position;	// in �̶� ����� �̰��� ATTRIBUTE (VS INPUT)
in vec3 a_Vel;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.f, -0.8f, 0.f);

void main()
{
	vec4 newPosition;
	// CPU -> GPU �ѱ�� �� ������ ������ ������ ��ģ��. ���� ������.
	// ������ �ð��� ���� ���� �ĺ��� ������ �ð��̴�. �����Ӱ� ������ ������ �ð��� �ƴϴ�. 
	// P = C(�ʱ���ġ) + V0(�ӵ�) * t(�����ð�)
	// �߷� - 1/2gt^2 �� ���� �Ŀ� ���Ѵ�. 
	newPosition.xyz = a_Position 
					  + a_Vel * u_Time // �ӵ��� ���� ��ġ 
					  + 0.5 * c_Gravity * u_Time * u_Time;	// �߷� �߰�
	newPosition.w = 1.f;
	gl_Position = newPosition;
}
