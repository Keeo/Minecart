#version 330 core
#extension GL_ARB_explicit_attrib_location : require

//uniform sampler2D sampler;

in vec2 uv;
in vec3 normal;
in vec3 position;

out vec3 color;

void main()
{
    color = normalize(position + normalize(normal));
}
