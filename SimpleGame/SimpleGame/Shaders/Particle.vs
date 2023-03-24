#version 330

in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
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
	// 기출 문제!! 1 주기만 출력하고 싶은 경우 바꾸기
	// newPosition.y = a_Position.y + sin(t); << 원래는 이건데 밑으로 바꾸면 1주기 됨.
	// 밑에 식에 2 주기로 바꾸고 싶으면 곱하기 2 하면 됨.
	float yTime = (t/10.f) * 2.0 * c_PI;
	newPosition.y = a_Position.y + sin(yTime);
	newPosition.z = a_Position.z + t * c_Vel.z;
	newPosition.w = 1.f;


	/*float t = u_Time - a_EmitTime;
	vec4 newPosition = vec4(0, 0, 0, 1);
	// CPU -> GPU 넘기는 건 굉장히 복잡한 절차를 걸친다. 성능 느려짐.
	// 앞으로 시간은 게임 시작 후부터 누적된 시간이다. 프레임과 프레임 사이의 시간이 아니다. 

	if ( t < 0.0 ) // 시간이 음수일 경우는 아직 보이면 안 되기 때문에 조건 
	{
		
	}
	else {
		// newT 는 2 초(라이프타임)이 지난 후에 계산하는 용도다.
		// t/a_lifeTime 을 하면 2초 단위로 0~1 사이의 값이 나온다. 그것을 lifeTime 곱해서 2초로 만들어준다.
		// 결국 0~2초마다 새롭게 위치가 계산되는 것임.
		float newT = a_lifeTime * fract(t/a_lifeTime);
		// P = C(초기위치) + V0(속도) * t(누적시간)
		// 중력 - 1/2gt^2 도 위의 식에 더한다. 
		newPosition.xyz = a_Position 
						  + a_Vel * newT // 속도에 따른 위치 
						  + 0.5 * c_Gravity * newT * newT;	// 중력 추가
		newPosition.w = 1.f;
	}*/

	gl_Position = newPosition;
}
