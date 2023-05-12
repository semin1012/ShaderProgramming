#version 330
 
layout(location=0) out vec4 FragColor;

uniform sampler2D u_TexSampler;

uniform vec2 u_XYRepeat = vec2(2, 2);
uniform int u_AnimStep = 0;

in vec2 v_TexPos;

void second() {
	float x = fract(v_TexPos.x * 2);
	float x2 = (floor(v_TexPos.x * 2)) * 0.5;
	float y = fract(v_TexPos.y * 2);

	y = fract(y + x2);
	
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

void P2()
{
	float x = fract(v_TexPos.x * 3.0);
	float dy = v_TexPos.y / 3.0;
	float y = floor(3.0*(1.0-v_TexPos.x)) / 3.0 + dy;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(y/2.0);
}

void P3()
{
	float x = v_TexPos.x;
	float dy = fract(v_TexPos.y*3.0)/3.0;
	float y = floor(3.0*(1.0-v_TexPos.y)) / 3.0 + dy;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
	//FragColor = vec4(y/2.0);
}

void P4()
{
	float tx = fract(v_TexPos.x * 3.0);
	float ty = v_TexPos.y + floor(v_TexPos.x * 3.0) / 3;
	FragColor = texture(u_TexSampler, vec2(tx, ty));
}


void P5()
{
	float x_repeat = u_XYRepeat.x;
	float y_repeat = u_XYRepeat.y;
	float dx = v_TexPos.x * x_repeat;
	float x = dx + floor((1.0 - v_TexPos.y) * y_repeat) * 0.5;
	float y = fract(v_TexPos.y * y_repeat);
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}


void P6()
{
	float x_repeat = u_XYRepeat.x;
	float y_repeat = u_XYRepeat.y;
	float dy = v_TexPos.y * y_repeat;
	float x = fract(v_TexPos.x * x_repeat);
	float y = fract(dy + floor(v_TexPos.x * x_repeat) * 0.5);
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos);
}


void P7()
{
	//float x_repeat = u_XYRepeat.x;
	//float y_repeat = u_XYRepeat.y;
	float y = fract(v_TexPos.x + v_TexPos.y);
	float x = fract(v_TexPos.x + (1.0 - v_TexPos.y));
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos); 
	//FragColor = vec4(x);
}

// case:: separated texture
void MultiTexture()
{
	FragColor = texture(u_TexSampler, v_TexPos);
}

// case:: Merge Texture
void MergeTexture()
{
	float x = v_TexPos.x;
	float y = u_AnimStep / 6.0 + v_TexPos.y/6.0;
	vec2 newTexPos = vec2(x, y);
	FragColor = texture(u_TexSampler, newTexPos); 
}

void main()
{
	//FragColor = vec4(v_TexPos, 0, 1);

	//float y = 1.0 - abs(v_TexPos.y * 2.0 - 1.0);
	
	MergeTexture();
}
