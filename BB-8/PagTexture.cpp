#include "PagTexture.h"

#include "SOIL.h"

PagTexture::PagTexture(): img(nullptr), imgWidth(0), imgHeight(0) {
}

PagTexture::PagTexture(std::string imgPath, GLuint _texture){
	texture = _texture;

	glGenTextures(_texture + 1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	img = SOIL_load_image(imgPath.c_str(),
		&imgWidth,
		&imgHeight,
		0,
		SOIL_LOAD_RGBA);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);
}


PagTexture::~PagTexture() {}
