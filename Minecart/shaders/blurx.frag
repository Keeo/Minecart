#version 330 core
#extension GL_ARB_explicit_attrib_location : require

uniform sampler2D image;

in vec2 uv;

out vec4 color;

uniform float offset[5] = float[]( 0.0, 1.0, 2.0, 3.0, 4.0 );
uniform float weight[5] = float[]( 0.2270270270, 0.1945945946, 0.1216216216,
                                   0.0540540541, 0.0162162162 );

void main(void)
{
    color = texture2D( image, uv ) * weight[0];
    for (int i=1; i<5; i++) {
        color += texture2D( image, uv + vec2(offset[i], 0.0) / 1024.0) * weight[i];
        color += texture2D( image, uv - vec2(offset[i], 0.0) / 1024.0) * weight[i];
    }
}
