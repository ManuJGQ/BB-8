#version 400

in vec3 position;
in vec3 normal;

uniform vec3 lightPosition;
uniform vec3 lightDirection;
uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float Shininess;

uniform float y;
uniform float s;

layout (location = 0) out vec4 FragColor;

vec3 ads(){
	vec3 n;
	if (gl_FrontFacing){
		n = normalize( normal );
	}else{
		n = normalize( -normal );
	}
	vec3 l = normalize( lightPosition-position );
	vec3 v = normalize( -position );
	vec3 d = normalize( lightDirection );
	vec3 r = reflect( -l, n );
	vec3 ambient = (Ia * Ka);
	vec3 diffuse = (Id * Kd * max( dot(l,n), 0.0));
	vec3 specular;
	specular = (Is * Ks * pow( max( dot(r,v), 0.0), Shininess));
	float sf;
	float Y = (y * 3.14) / 180;
	if(dot(-l,lightDirection) >= cos(Y)){
		sf = pow( dot(-l,d), s);
	}else{
		sf = 0;
	}
	return ambient + sf * (diffuse + specular);
}

void main() {
	FragColor = vec4(ads(), 1.0);
}