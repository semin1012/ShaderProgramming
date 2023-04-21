#version 330

in vec3 a_Position;

const float PI = 3.141592;

uniform float u_Time;

out float v_Alpha;
out float v_Time;

void main()
{
	
	float value = PI*(a_Position.x + 1.0);
	float d = a_Position.x - (-1.f);
	float newY = d * sin(value - u_Time) * 0.2;
	// ÆøÀÌ ³Ê¹« Ä¿¼­ 0.5 °öÇÔ
	vec4 newPos = vec4(a_Position, 1.0f);
	newPos.y = newY;
	gl_Position = newPos;

	v_Alpha = 0.f;
	v_Alpha = 1.0 - (a_Position.x + 1.0) / 2.0;
	v_Time = u_Time;
}
