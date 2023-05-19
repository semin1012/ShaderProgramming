#version 330

layout(location=0) out vec4 FragColor;

varying vec4 v_Color;	// in vecter4 vertex
in vec2 v_UV;

uniform sampler2D u_Texture;

void circle()
{
	vec2 temp = v_UV - vec2(0.5f, 0.5f);
	float distance = length(temp);
	if ( distance < 0.5f ) 
	{
		FragColor = vec4(1.f) * v_Color;
	}
	else 
	{
		FragColor = vec4(0.f);
	}
}

void circles()
{
	vec2 temp = v_UV - vec2(0.5f, 0.5f);
	float distance = length(temp);
	float value = sin(30*distance);
	
	FragColor = vec4(value);
	// 동심원 그리기, 기출문제 중 하나
	// 몇개의 주기인지 같은 것 다 똑같이 해야 함
}

void Textured()
{
	vec4 result = texture(u_Texture, v_UV) * v_Color;
	FragColor = result;
}

void main()
{
	Textured();
}
