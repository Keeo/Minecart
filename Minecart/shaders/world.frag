#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform vec3 light;
uniform vec3 ambientLight;

uniform sampler2D sampler;

in vec2 uv;
in vec3 normal;
in vec3 position;

out vec3 color;

void main()
{
    vec3 N = normalize(normal);
    vec3 lightColor = vec3(0);
    vec3 L = light - position;
    vec3 V = normalize(light - position);
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

    color =  /*texture(sampler, uv).rgb*/ vec3(0.0f,0.6f,0.0f) * lightColor * ambientLight;// * vec3(uv.x, uv.y, 1.0);

    /// calculate fog vactor
    float distance = length(light - position);
    float fog = exp2( -0.02 * 0.02 * distance * distance * 1.442695 );
    fog = clamp(fog, 0.1, 1.0);
    color = texture(sampler, uv).rgb;
    color = normalize(position + normalize(normal));
    //color = mix(vec3(0.1,0.1,0.1), color, fog);
}
