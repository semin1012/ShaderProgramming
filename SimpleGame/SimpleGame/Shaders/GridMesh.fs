#version 330

layout(location=0) out vec4 FragColor;
uniform sampler2D u_Texture;

in vec2 v_TexPos;
in float v_greyScale;


void main()
{
	//FragColor = vec4(v_TexPos, 0, 1);
	//FragColor = texture(u_Texture, v_TexPos);

	vec2 newTexPos = fract(v_TexPos * 2.0);
	FragColor = 0.5 * (v_greyScale+1.0+0.2) * texture(u_Texture, newTexPos);
}
