#include "PagLight.h"
#include <iostream>

PagLight::PagLight(){}

PagLight::PagLight(glm::vec3 _positionDirection, float _Ia, float _Id, float _Is,
	glm::vec3 _Ks, char _light, float _shininess): shadowMapWidth(2048), shadowMapHeight(2048), needRecalcShadows(true) {

	if (_light == 'P') {

		light = 'P';

		position = _positionDirection;

		Ia = _Ia;
		Id = _Id;
		Is = _Is;

		Ks = _Ks;

		shininess = _shininess;

	}
	else if (_light == 'D') {

		light = 'D';

		direction = _positionDirection;

		Ia = _Ia;
		Id = _Id;
		Is = _Is;

		Ks = _Ks;

		shininess = _shininess;

	}
}


PagLight::PagLight(glm::vec3 _position, glm::vec3 _direction, float _Ia, float _Id, float _Is,
	glm::vec3 _Ks, float _y, float _s, float _shininess): shadowMapWidth(2048), shadowMapHeight(2048), needRecalcShadows(true) {

	light = 'S';

	position = _position;
	direction = _direction;

	Ia = _Ia;
	Id = _Id;
	Is = _Is;

	Ks = _Ks;

	y = _y;
	s = _s;

	shininess = _shininess;

}

PagLight::PagLight(const PagLight & orig) {
	shadowFBO = orig.shadowFBO;
	depthTex = orig.depthTex;

	shadowMapWidth = orig.shadowMapWidth;
	shadowMapHeight = orig.shadowMapHeight;


	needRecalcShadows = needRecalcShadows;
	
	light = orig.light;
	if (light == 'S') {
		position = orig.position;
		direction = orig.direction;

		Ia = orig.Ia;
		Id = orig.Id;
		Is = orig.Is;

		Ks = orig.Ks;

		y = orig.y;
		s = orig.s;

		shininess = orig.shininess;
	}
	else {
		if (light == 'P') {
			position = orig.position;

			Ia = orig.Ia;
			Id = orig.Id;
			Is = orig.Is;

			Ks = orig.Ks;

			shininess = orig.shininess;
		}
		else {
			direction = orig.direction;

			Ia = orig.Ia;
			Id = orig.Id;
			Is = orig.Is;

			Ks = orig.Ks;

			shininess = orig.shininess;
		}
	}
}

void PagLight::operator=(const PagLight & orig){
	*this = orig;
}

void PagLight::crearFBOShadowsMap(GLuint n) {
	GLuint depthTex = n;
	GLuint shadowFBO = 0;

	GLfloat border[] = { 1.0, 1.0, 1.0, 1.0 };

	glGenTextures(n + 1, &depthTex);
	glBindTexture(GL_TEXTURE_2D, depthTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, shadowMapWidth,
		shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
		NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LESS);

	glGenFramebuffers(1, &shadowFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
		GL_TEXTURE_2D, depthTex, 0);
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (result != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "Framebuffer for shadows is not complete" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0 );
}

PagLight::~PagLight(){}
