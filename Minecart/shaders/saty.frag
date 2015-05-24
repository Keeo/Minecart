#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D image;
uniform int pass;

in vec2 uv;

out vec4 color;

void main(void)
{
	vec2 lookup = vec2(0, pow(2.0f, float(pass)) / 768.0f);
    color = texture2D(image, uv) + texture2D(image, uv + lookup);
}
