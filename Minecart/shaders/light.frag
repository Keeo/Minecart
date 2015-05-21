#version 330 core

uniform vec3 lightPosition;
uniform vec3 camPosition;
uniform sampler2D shadow;

in vec3 vertex_pos;
in vec3 v_normal;
in vec2 uv;
in vec4 ShadowCoord;
in float depth;

out vec3 color;

void main()
{
	color = normalize(vertex_pos);
	//color *= texture( shadow, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );
	

	//vec2 s = texture(shadow, ShadowCoord.xy).xy;
	/*if (ShadowCoord.z < 0.0) {
		return;
	}*/
	//float bias = 0.000005;
	if ( textureProj( shadow, (ShadowCoord.xyw) ).x  >  ((ShadowCoord.z)/ShadowCoord.w) ) {
	//if ( textureProj( shadowMap, ShadowCoord.xyw ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w )

	//if (texture( shadow, ShadowCoord.xy ).r > ShadowCoord.z) {
		color += vec3(0.2,0.2,0.2);// * distance(lightPosition, camPosition);
	} else {
		color -= vec3(0.2,0.2,0.2);
	}
	color = clamp(color,0,1);
}
