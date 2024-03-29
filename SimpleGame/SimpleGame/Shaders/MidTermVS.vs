#version 330

in vec3 a_Position;
in vec2 a_TexPos;
in float a_Value;
uniform float u_Time;
const float PI = 3.141592;

out vec2 v_TexPos;

void First()
{
	float x = a_Position.x + sin(u_Time);
	float y = a_Position.y + cos(u_Time);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void Second()
{
	float x = a_Position.x + 2 * fract(u_Time)-1;
	float y = a_Position.y + sin(u_Time*2*PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void Third()
{
	float sign = 2 * (a_Value - 1.5);
	float x = a_Position.x - sign * 2 * fract(u_Time) - sign;
	float y = a_Position.y + sin(u_Time * 2.0 * PI);
	vec4 newPosition = vec4(x, y, 0.0, 1.0);
	gl_Position = newPosition;
	v_TexPos = a_TexPos;
}

void main()
{
	
}