#version 330

in vec3 a_Position; //ATTRIBUTE (VS INPUT)
in vec2 a_Texcoord;

out vec2 v_Texcoord;

void main()
{
	gl_Position = vec4(a_Position, 1.0);
	v_Texcoord = a_Texcoord;
}
