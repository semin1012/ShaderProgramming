#version 330

in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
in vec3 a_Vel;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.f, -0.8f, 0.f);

void main()
{
	vec4 newPosition;
	// CPU -> GPU 넘기는 건 굉장히 복잡한 절차를 걸친다. 성능 느려짐.
	// 앞으로 시간은 게임 시작 후부터 누적된 시간이다. 프레임과 프레임 사이의 시간이 아니다. 
	// P = C(초기위치) + V0(속도) * t(누적시간)
	// 중력 - 1/2gt^2 도 위의 식에 더한다. 
	newPosition.xyz = a_Position 
					  + a_Vel * u_Time // 속도에 따른 위치 
					  + 0.5 * c_Gravity * u_Time * u_Time;	// 중력 추가
	newPosition.w = 1.f;
	gl_Position = newPosition;
}
