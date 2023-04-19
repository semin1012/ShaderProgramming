#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Texcoord;

uniform vec2 u_Point;
uniform vec2 u_Points[3];
uniform float u_Time;
const float c_PI = 3.141592;

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
	vec2 temp = v_Texcoord - u_Points[0];
	float distance = length(temp);
	temp = v_Texcoord - u_Points[1];
	float distance1 = length(temp);
	if ( distance < 0.1f || distance1 < 0.1f) 
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
	vec2 temp = v_Texcoord - u_Point;
	float distance = length(temp);
	float value = 0.2 * pow(sin(distance * 2 * c_PI - u_Time), 12);
	//float temp = ceil(value);
	// Pow = ���� ��� �ϱ� ����, 0.2 �� ���ϸ� ������
	
	FragColor = vec4(value);
	// ���ɿ� �׸���, ���⹮�� �� �ϳ�
	// ��� �ֱ����� ���� �� �� �Ȱ��� �ؾ� ��
}

void radar()
{
	vec2 temp = v_Texcoord - vec2(0.5f, 0.5f);
	vec4 result = vec4(0);
	float distance = length(temp);
	float value = 0.2 *( pow(sin(distance * 2 * c_PI - u_Time), 12) - 0.5);
	float temp1 = ceil(value);

	for ( int i = 0 ; i < 3; i++ ){
		vec2 temp = v_Texcoord - u_Points[i];
		distance = length(temp);

		if ( distance < 0.1f ) 
		{
			//result += 1.f * temp1;
		}
	}	

	FragColor = vec4(result + 10 * value);
}

void main()
{
	radar();
	// ��ġ���� ��ȭ�� ���� ��µǴ� ������ ������ ��ģ��.
}
