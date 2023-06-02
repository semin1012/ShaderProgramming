#version 330

in vec3 a_Position;	// in 이라 선언된 이것이 ATTRIBUTE (VS INPUT)
in vec3 a_Vel;
in float a_EmitTime;
in float a_LifeTime;
in float a_Period;
in float a_Amp;
in float a_Value;
in vec4 a_Color;
in vec2 a_UV;

uniform float u_Time;

const vec3 c_Gravity = vec3(0.f, -0.8f, 0.f);
const float c_lifeTime = 2.0f;
const vec3 c_Vel = vec3(0.0, 0.5, 0.0);
const float c_PI = 3.141592;
const float c_Period = 1.0f;
const float c_Amp = 1.0f;

varying vec4 v_Color;	// out vecter4 vertex
varying vec2 v_UV;

void GraphSin()
{
   float t = u_Time - a_EmitTime;

	vec4 newPosition = vec4(0, 0, 0, 1);
	float newAlpha = 0.0;
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

		newAlpha = 1.f - newT/a_LifeTime;
		newAlpha = pow(newAlpha, 0.2);	// set speed (speed down -> 0.2, speed up -> 10)
   }

	gl_Position = newPosition;
	v_Color = vec4( a_Color.rgb, a_Color.a * newAlpha);	// add Color

}

void main()
{

	GraphSin();

	v_UV = a_UV;
	//gl_Position = P1();
}
