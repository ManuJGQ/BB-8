#pragma once

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include "glm.hpp"

#include <iostream>

class PagTexture {
	GLuint texture;
	unsigned char* img;
	int imgWidth;
	int imgHeight;
public:
	PagTexture();
	PagTexture(std::string imgPath, GLuint _texture);
	GLuint getTexture() { return texture; }

	/*PagTexture operator< (const PagTexture &orig) {
		if (texture < orig.texture) {
			return *this;
		}
		return orig;
	}*/

	~PagTexture();
};

