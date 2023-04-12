#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Texcoord;

void test()
{
	if ( v_Texcoord.x > 0.5f ) 
	{
		FragColor = vec4(v_Texcoord, 0.f, 1.f);
	}
	else 
	{
		FragColor = vec4(0.f);
	}
}

void circle()
{
	vec2 temp = v_Texcoord - vec2(0.5f, 0.5f);
	float distance = length(temp);
	if ( distance < 0.5f ) 
	{
		FragColor = vec4(1.f);
	}
	else 
	{
		FragColor = vec4(0.f);
	}
}

void circles()
{
	vec2 temp = v_Texcoord - vec2(0.5f, 0.5f);
	float distance = length(temp);
	float value = sin(30*distance);
	
	FragColor = vec4(value);
	// 동심원 그리기, 기출문제 중 하나
	// 몇개의 주기인지 같은 것 다 똑같이 해야 함
}

void main()
{
	circles();
	// 위치에는 변화가 없고 출력되는 색에만 영향을 미친다.
}
