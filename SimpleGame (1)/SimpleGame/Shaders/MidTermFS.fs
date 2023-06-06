#version 330

layout(location=0) out vec4 FragColor;
in vec2 v_TexPos;
uniform sampler2D u_TexSampler;

void main()
{
    float tx = fract(v_TexPos.x*3.0);
    float ty = v_TexPos.y+(floor(v_TexPos.x*3.0) / 3);
    FragColor = texture(u_TexSampler, vec2(tx, ty));
}
