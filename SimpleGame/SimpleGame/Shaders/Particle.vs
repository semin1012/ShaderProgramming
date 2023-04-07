#version 330

in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
in vec3 a_Vel;
in float a_EmitTime;
in float a_LifeTime;
in float a_Period;
in float a_Amp;
in float a_Value;
in vec4 a_Color;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.f, -0.8f, 0.f);
const float c_lifeTime = 2.0f;
const vec3 c_Vel = vec3(0.0, 0.5, 0.0);
const float c_PI = 3.141592;
const float c_Period = 1.0f;
const float c_Amp = 1.0f;

varying vec4 v_Color;	// out vecter4 vertex

vec4 GraphSin()
{
   float t = u_Time - a_EmitTime;

	vec4 newPosition = vec4(0, 0, 0, 1);
   if(t < 0)
   {
      
   }
   else
   {
		float newT = a_LifeTime *  fract(t / a_LifeTime);
		float nX = sin(a_Value * 2.0 * c_PI);	// 2 Pi
		float nY = cos(a_Value * 2.0 * c_PI);	// 2 Pi

		newPosition.x = a_Position.x + 0.7 * nX + newT * c_Vel.x;
		newPosition.y = a_Position.y + 0.7 * nY + newT * c_Vel.y;
		// 0.5 = size setting

		vec2 newDir = vec2(-c_Vel.y, c_Vel.x);
		newDir = normalize(newDir);
		newPosition.xy += newDir * (newT * a_Amp * sin(a_Period * newT * 2.0 * c_PI));
   }

	return newPosition;
}

void main()
{
	gl_Position = GraphSin();
	v_Color = a_Color;	// add Color
	//gl_Position = P1();
}
