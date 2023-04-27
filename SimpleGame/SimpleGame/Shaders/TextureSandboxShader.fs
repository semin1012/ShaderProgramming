#version 330

layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;
in vec2 v_TexPos;

void second() {
	float x = v_TexPos.x * 3;
	float y_dis = 0.0;
	if ( x < 2 )
	{
		if ( x < 1 ){
			y_dis += 2.0/3.0;
		}
		else {
			y_dis += 1.0/3.0;
		}
	}
	float d = 1.0/3.0;
	float y = (v_TexPos.y / 3) + y_dis;
	
	
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void final()
{
	float x = v_TexPos.x;
	float y, d;
	if ( v_TexPos.y < 2.0 / 3.0 ){
		if ( v_TexPos.y < 1.0 / 3.0 ){
			d = 2.0/3.0;
		}
		else d = 0;
	}
	else d = 1.0/3.0;
	y = v_TexPos.y + d;

	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}

void main()
{
	//FragColor = vec4(v_TexPos, 0, 1);

	//float y = 1.0 - abs(v_TexPos.y * 2.0 - 1.0);
	
	second();
}
