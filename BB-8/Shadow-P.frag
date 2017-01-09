#version 400

in vec3 position;
in vec3 normal;
in vec4 shadowCoord;

uniform vec3 lightPosition;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float Shininess;

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

vec3 ads() {
	vec3 n;
	if (gl_FrontFacing){
		n = normalize( normal );
	}else{
		n = normalize( -normal );
	}
	vec3 l = normalize( lightPosition-position );
	vec3 v = normalize( -position );
	vec3 r = reflect( -l, n );
	vec3 ambient = (Ia * Ka);
	vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));
	vec3 specular;
	specular = (Is * Ks * pow( max( dot(r,v), 0.0), Shininess));

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
	FragColor = vec4(ads(), 1.0);
}