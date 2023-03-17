#version 330

in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)

void main()
{
	vec4 newPosition;
	newPosition.xyz = a_Position;
	newPosition.w = 1.f;
	gl_Position = newPosition;
}
