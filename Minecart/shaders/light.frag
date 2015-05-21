#version 330 core

uniform vec3 lightPosition;
uniform vec3 camPosition;
uniform sampler2D shadow;

in vec3 vertex_pos;
in vec3 v_normal;
in vec2 uv;
in vec4 ShadowCoord;
in float depth;

in vec3 l;
in vec3 n;

out vec3 color;

void main()
{
	float cosTheta = clamp( dot( normalize(n), normalize(l) ), 0,1 );
 	float light = 1;
	color = normalize(vertex_pos);

	/*if (ShadowCoord.z < 0.0) {
		return;
	}*/
	//float bias = 0.000005;
	if ( textureProj( shadow, (ShadowCoord.xyw) ).x  >  (ShadowCoord.z/ShadowCoord.w) ) {
		light = 1;
		//color += vec3(0.2,0.2,0.2) * cosTheta;
	} else {
		light = 0.1;
		//color -= vec3(0.2,0.2,0.2) * cosTheta;
	}
	float distance = length( lightPosition - vertex_pos );
	float power = 500;
	color *= min(cosTheta, light) * power / (distance * distance);
	color = clamp(color,0,1);
}
