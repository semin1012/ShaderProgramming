#version 330

layout(location = 0) in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
// 결국 인덱스를 알아야 한다는 것인데, 0인지 1인지 어떻게 아는가. 자동으로 생성됨.
// 0을 넣으면 위험한 코드임. 그래서 layout(location = 0) 이라 하면 0번의 로케이션을 가지게 됨. 안전.

uniform vec4 u_Trans;
//
layout(location = 0) in vec3 b_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
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
