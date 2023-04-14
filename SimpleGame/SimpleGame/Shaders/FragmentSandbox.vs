#version 330

in vec3 a_Position;	
in vec2 a_Texcoord;
in vec3 a_Vel;
in vec2 a_UV;

out vec2 v_Texcoord;

void main()
{
	gl_Position = vec4(a_Position, 1.f);
	//gl_Position = vec4( 0.5 * a_Position + vec3(0.2, 0.0, 0.0), 1.f);
	//vs decided position
	v_Texcoord = a_Texcoord;
}
