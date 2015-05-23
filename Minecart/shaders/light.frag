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

float diffuseLight()
{
	//return 1;
	float cosTheta = clamp( dot( normalize(n), normalize(l) ), 0,1 );

	float distance = length( lightPosition - vertex_pos );
	float power = 500;
	return cosTheta;// * power / (distance * distance);
}

float chebyshevUpperBound( float distance, vec4 ShadowCoordPostW)
{
	vec2 moments = texture2D(shadow, ShadowCoordPostW.xy).rg;
	
	// Surface is fully lit. as the current fragment is before the light occluder
	if (distance <= moments.x)
		return 1.0 ;

	// The fragment is either in shadow or penumbra. We now use chebyshev's upperBound to check
	// How likely this pixel is to be lit (p_max)
	float variance = moments.y - (moments.x*moments.x);
	variance = max(variance, 0.00002);

	float d = distance - moments.x;
	float p_max = variance / (variance + d*d);

	return p_max;
}

void main()
{
 	float light = 1;
	color = normalize(vertex_pos);

	vec4 ShadowCoordPostW = ShadowCoord / ShadowCoord.w;
	light = chebyshevUpperBound(ShadowCoord.z, ShadowCoordPostW);

	/*if ( textureProj( shadow, (ShadowCoord.xyw) ).x  >  (ShadowCoord.z)) {
		light = 1;
	} else {
		light = 0.1;
	}*/

	color *= diffuseLight() * light;
	color = clamp(color,0,1);
}
