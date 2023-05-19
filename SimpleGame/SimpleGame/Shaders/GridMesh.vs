#version 330

in vec3 a_Position;	
const float PI = 3.141592;

void SinTest()
{
	//float scale = 0.2;
	//vec3 trans = vec3(0.5, 0.5, 0.5);
	//size
	//vec4 newPosition = vec4(a_Position * scale + trans, 1.0);
	
	float x = a_Position.x;
	float value = (a_Position.x + 0.5) * 2.0 * PI;
	float y = a_Position.y + 0.5 * sin(value);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
}


void main()
{
	//�����׸�Ʈ ���̴��� �޸� ���ؽ��� ���� ���ִ� �ε巴�� ����
	//�ε巴�� �Ϸ��� ���ؽ� ī��Ʈ�� �ø��� ����ۿ� ����.
	SinTest();
}
