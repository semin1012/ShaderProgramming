#version 330

in vec3 a_Position;	// in �̶� ����� �̰��� ATTRIBUTE (VS INPUT)
in vec3 a_Vel;
in float a_EmitTime;
in float a_lifeTime;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.f, -0.8f, 0.f);
const float c_lifeTime = 2.0f;
const vec3 c_Vel = vec3(0.1, 0.0, 0.0);
const float c_PI = 3.141592;

void main()
{
	vec4 newPosition = vec4(0, 0, 0, 1);
	float t = 10.f * fract(u_Time / 10.f);
	newPosition.x = a_Position.x + t * c_Vel.x;
	// ���� ����!! 1 �ֱ⸸ ����ϰ� ���� ��� �ٲٱ�
	// newPosition.y = a_Position.y + sin(t); << ������ �̰ǵ� ������ �ٲٸ� 1�ֱ� ��.
	// �ؿ� �Ŀ� 2 �ֱ�� �ٲٰ� ������ ���ϱ� 2 �ϸ� ��.
	float yTime = (t/10.f) * 2.0 * c_PI;
	newPosition.y = a_Position.y + sin(yTime);
	newPosition.z = a_Position.z + t * c_Vel.z;
	newPosition.w = 1.f;


	/*float t = u_Time - a_EmitTime;
	vec4 newPosition = vec4(0, 0, 0, 1);
	// CPU -> GPU �ѱ�� �� ������ ������ ������ ��ģ��. ���� ������.
	// ������ �ð��� ���� ���� �ĺ��� ������ �ð��̴�. �����Ӱ� ������ ������ �ð��� �ƴϴ�. 

	if ( t < 0.0 ) // �ð��� ������ ���� ���� ���̸� �� �Ǳ� ������ ���� 
	{
		
	}
	else {
		// newT �� 2 ��(������Ÿ��)�� ���� �Ŀ� ����ϴ� �뵵��.
		// t/a_lifeTime �� �ϸ� 2�� ������ 0~1 ������ ���� ���´�. �װ��� lifeTime ���ؼ� 2�ʷ� ������ش�.
		// �ᱹ 0~2�ʸ��� ���Ӱ� ��ġ�� ���Ǵ� ����.
		float newT = a_lifeTime * fract(t/a_lifeTime);
		// P = C(�ʱ���ġ) + V0(�ӵ�) * t(�����ð�)
		// �߷� - 1/2gt^2 �� ���� �Ŀ� ���Ѵ�. 
		newPosition.xyz = a_Position 
						  + a_Vel * newT // �ӵ��� ���� ��ġ 
						  + 0.5 * c_Gravity * newT * newT;	// �߷� �߰�
		newPosition.w = 1.f;
	}*/

	gl_Position = newPosition;
}
