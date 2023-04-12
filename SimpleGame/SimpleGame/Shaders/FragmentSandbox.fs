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
	// ���ɿ� �׸���, ���⹮�� �� �ϳ�
	// ��� �ֱ����� ���� �� �� �Ȱ��� �ؾ� ��
}

void main()
{
	circles();
	// ��ġ���� ��ȭ�� ���� ��µǴ� ������ ������ ��ģ��.
}
