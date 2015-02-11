#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec4 vertex_position;

out vec2  uv;
 
void main()
{
	//gl_Position = /*projection * view * model **/ vertex_position;
	gl_Position = vec4(vertex_position.xy, 0.0, 1.0);
	//gl_Position = sign( gl_Position );
	 
	// Texture coordinate for screen aligned (in correct range):
	uv = (vec2( gl_Position.x, + gl_Position.y ) + vec2( 1.0 ) ) * 0.5;
}