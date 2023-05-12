#version 330

layout(location=0) out vec4 FragColor;

in vec2 v_Texcoord;

uniform vec2 u_Point;
uniform vec2 u_Points[3];
uniform float u_Time;
const float c_PI = 3.141592;

void test()
{
	// 100.0 - lines num
	float newValueX = v_Texcoord.x * 10.0 * c_PI;
	float outColorGreyVertical = sin(newValueX);
	
	float newValueY = v_Texcoord.y * 10.0 * c_PI;
	float outColorGreyHorizontal = sin(newValueY);

	float newColor = max(outColorGreyVertical, outColorGreyHorizontal);
	FragColor = vec4(newColor);
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
	vec2 temp = v_Texcoord - u_Points[0];
	vec4 result = vec4(0);
	float distance = length(temp);
	float value = 0.2 *( pow(sin(distance * 2 * c_PI - u_Time), 12) - 0.5);

	FragColor = vec4(result + 10 * value);
}

void flag()
{
	float FinalColor = 0;
	for ( int i = 0 ; i < 5; i++ )
	{
		float newTime = u_Time + i * 0.2;

		float newColor = v_Texcoord.x * 0.5 * sin(v_Texcoord.x*c_PI*2 - 10 * newTime);
		float sinValue = sin(v_Texcoord.x * c_PI * 2 * 70);
		//  0.5 - height
		float width = 0.01 * v_Texcoord.x * 30;
		if ( 2 * ( v_Texcoord.y - 0.5 ) > newColor && 2 * (v_Texcoord.y - 0.5) < newColor + width )	// line
		// if ( 2 * (v_Texcoord.y - 0.5) > newColor )
		// -> fill
		{
			FinalColor += 1 * sinValue * (1.0 - v_Texcoord.x);
			// 1 - v_Texcoord.x -> more alpha down
		}
		else 
		{
		}

	}
	FragColor = vec4(FinalColor);
	
}

void main()
{
	//radar();
	// ��ġ���� ��ȭ�� ���� ��µǴ� ������ ������ ��ģ��.
	radar();
	//test();
}
