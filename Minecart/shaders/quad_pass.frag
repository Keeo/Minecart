#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D image;
uniform sampler2D ssao;

in vec2 uv;

out vec4 color;

void main(void)
{
    color = texture2D( image, uv ) * texture2D( ssao, uv );
}
