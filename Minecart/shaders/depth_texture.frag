#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;
uniform vec3 camPosition;

in vec2 uv;
flat in vec3 v_normal;
in vec3 position;
uniform vec3 lightPosition;

out vec2 color;
in float depth;

void main()
{
	float depth = length(position - lightPosition);
	//depth -= 0.5f;

	float dx = dFdx(depth);
	float dy = dFdy(depth);
	color.r = depth;
	color.g = depth * depth;
	color.g += 0.25*(dx*dx+dy*dy);
	color -= vec2(34.0f, 1250.0f);

}
