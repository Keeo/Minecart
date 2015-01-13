#version 330 core
#extension GL_ARB_explicit_attrib_location : require

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec2 vertex_uv;
layout(location = 5) in vec3 vertex_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 uv;
out vec3 normal;
out vec3 position;

// gl_vertexid;
void main()
{
    gl_Position = projection * view * model * vec4(vertex_position, 1);
    position = vec3(model * vec4(vertex_position, 1.0));
    uv = vertex_uv;
    normal = vertex_normal;
}

