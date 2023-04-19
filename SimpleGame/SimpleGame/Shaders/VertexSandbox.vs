#version 330

in vec3 a_Position;	

uniform float u_Time;

const float PI = 3.141592;
void main()
{
	float value = PI*(a_Position.x + 1.0);
	float d = a_Position.x - (-1.f);
	float newY = d * sin(value - u_Time) * 0.5;
	// ÆøÀÌ ³Ê¹« Ä¿¼­ 0.5 °öÇÔ
	vec4 newPos = vec4(a_Position, 1.0f);
	newPos.y = newY;

	gl_Position = newPos;
}
