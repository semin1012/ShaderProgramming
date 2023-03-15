#version 330

layout(location = 0) in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
// 결국 인덱스를 알아야 한다는 것인데, 0인지 1인지 어떻게 아는가. 자동으로 생성됨.
// 0을 넣으면 위험한 코드임. 그래서 layout(location = 0) 이라 하면 0번의 로케이션을 가지게 됨. 안전.
layout(location = 1) in vec3 a_Position1;
// layout(location = 1) 같은 코드를 안 써도 되긴 한데, 그럼 0번인지 1번인지 장담할 수가 없어서 코드 위험해짐.
uniform vec4 u_Trans;

void main()
{
	vec4 newPosition;
	newPosition.xy = (a_Position.xy + a_Position1.xy ) *u_Trans.w + u_Trans.xy;
	newPosition.z = 0;
	newPosition.w= 1;
	gl_Position = newPosition;
}
