#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D sampler;

in vec2 uv;
in vec3 normal;
in vec3 position;
in vec3 light_position;

out vec3 color;


vec3 dumpLight()
{
    vec3 N = normalize(normal);
    vec3 lightColor = vec3(0);
    vec3 L = light_position - position;
    vec3 V = normalize(light_position - position);
    float dist = length(L)/2;
    L = normalize(L);
    vec3 R = reflect(-L, N);

    float attenuation = min(1.0f / pow(dist,2), 1.7f);

    /// ambient
    //lightColor += light[i].ambient * material.ambient;

    /// difuse component
    lightColor += vec3(0.9,0.95,0.8) * max(dot(N, L), 0.0f);

    /// specular component
    lightColor += vec3(1,1,0.9) * pow(max(dot(R,V),0), 4);
    return lightColor;
}

void main()
{
    //color = texture(sampler, uv).rgb;
    color = normalize(normalize(texture(sampler, uv).rgb) + normalize(position));
}


