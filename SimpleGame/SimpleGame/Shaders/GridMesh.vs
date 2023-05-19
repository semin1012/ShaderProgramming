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
	//프래그먼트 셰이더와 달리 버텍스는 각이 져있다 부드럽지 않음
	//부드럽게 하려면 버텍스 카운트를 늘리는 방법밖에 없다.
	SinTest();
}
