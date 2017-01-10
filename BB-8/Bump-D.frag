#version 400

in vec3 position;
in vec3 lDir;
in vec3 vDir;
in vec2 texCoord;

uniform vec3 Ks;
uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float Shininess;

uniform sampler2D TexSamplerColor;
uniform sampler2D TexSamplerBump;

layout (location = 0) out vec4 FragColor;

vec3 ads(vec4 texColor, vec4 normal){
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
	return ambient + diffuse + specular;
}

void main() {
	vec4 texColor = texture(TexSamplerColor, texCoord);
	vec4 normal = (2.0 * texture(TexSamplerBump, texCoord)) - 1.0;
	FragColor = vec4(ads(texColor, normal), 1.0);
}