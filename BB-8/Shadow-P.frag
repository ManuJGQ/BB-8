#version 400

in vec3 position;
in vec3 lDir;
in vec3 vDir;
in vec2 texCoord;
in vec4 shadowCoord;

uniform vec3 Ks;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float Shininess;

uniform sampler2D TexSamplerColor;
uniform sampler2D TexSamplerBump;

uniform float shadowMin;
uniform sampler2DShadow shadowMap;

layout (location = 0) out vec4 FragColor;

float shadowFactor() {
	float sum = 0;

	sum += textureProjOffset(shadowMap, shadowCoord, ivec2(-1,-1));
	sum += textureProjOffset(shadowMap, shadowCoord, ivec2(-1,1));
	sum += textureProjOffset(shadowMap, shadowCoord, ivec2(1,1));
	sum += textureProjOffset(shadowMap, shadowCoord, ivec2(1,-1));
	sum += textureProjOffset(shadowMap, shadowCoord, ivec2(0,0));

	float shadowFactor = sum * (1.0/5.0);

	shadowFactor = clamp(shadowFactor, shadowMin, 1.0);
	
	return shadowFactor;
}

vec3 ads(vec4 texColor, vec4 normal) {
	vec3 n = normal.rgb;
	if (gl_FrontFacing){
		n = normalize( n );
	}else{
		n = normalize( -n );
	}

	vec3 Kad = texColor.rgb;

	vec3 l = normalize( lDir );
	vec3 v = normalize( vDir );
	vec3 r = reflect( -l, n );

	vec3 ambient = (Ia * Kad);
	vec3 diffuse = (Id * Kad * max( dot(l,n), 0.0));
	vec3 specular;
	if (dot(l,n) < 0.0){
		specular = vec3(0.0);
	}else{
		specular = (Is * Ks * pow( max( dot(r,v), 0.0), Shininess));
	}

	float shadowFact = shadowFactor();
	float shadowMul4Specular;
	if (shadowFact < (1.0-0.000001)) {
		shadowMul4Specular = 0.0;
	} else {
		shadowMul4Specular = 1.0;
	}
	vec3 color = ambient +
	shadowFact * (diffuse + (shadowMul4Specular * specular));
	return color;
}

void main() {
	vec4 texColor = texture(TexSamplerColor, texCoord);
	vec4 normal = (2.0 * texture(TexSamplerBump, texCoord)) - 1.0;
	FragColor = vec4(ads(texColor, normal), 1.0);
}