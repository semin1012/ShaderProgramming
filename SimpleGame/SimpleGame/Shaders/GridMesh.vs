#version 330

in vec3 a_Position;	
const float PI = 3.141592;

uniform float u_Time;

out vec2 v_TexPos;
out float v_greyScale;

void SinTest()
{
	//float scale = 0.2;
	//vec3 trans = vec3(0.5, 0.5, 0.5);
	//size
	//vec4 newPosition = vec4(a_Position * scale + trans, 1.0);
	
	float x = a_Position.x;
	float temp = a_Position.x + 0.5;
	float value = (a_Position.x + 0.5) * 2.0 * PI;
	float y = a_Position.y + temp * 0.5 * sin(value - u_Time * 2);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;

	vec3 tarPosition = vec3(1.0, 1.0, 0.0);
	// 버텍스별로 시간을 달리 주는 게 포인트다
	float newTime = fract(u_Time) - a_Position.y;
	vec3 morphPosition = mix(newPosition.xyz, tarPosition, newTime);
	gl_Position = vec4(morphPosition, 1.0);

	float tx = a_Position.x + 0.5;
	float ty = a_Position.y * (-1) + 0.5;
	v_TexPos = vec2(tx, ty);
	v_greyScale = sin(value - u_Time * 2) + 0.5;
}


void main()
{
	//프래그먼트 셰이더와 달리 버텍스는 각이 져있다 부드럽지 않음
	//부드럽게 하려면 버텍스 카운트를 늘리는 방법밖에 없다.
	SinTest();
}
