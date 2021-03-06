#include <iostream>

#include "PagCamera.h"

#include <math.h>

#define PI 3.14159265358979323846

/**
 * Constructor por defecto de la clase PagCamera
 */
PagCamera::PagCamera() : mouseX(0), mouseY(0), rotates(false), truck(false), orbit(false), ejecutandoOrbit(false), indOrbit(0), zOrbit(0) {
	x = 0.0;
	y = 80.0;
	z = -80.0;
	xLookAt = 0.0;
	yLookAt = 0.0;
	zLookAt = 0.0;
	fovY = 45.0f;
	ProjectionMatrix *= glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 2000.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
}

/**
* Constructor parametrizado de la clase PagCamera
*/
PagCamera::PagCamera(double _x, double _y) : mouseX(512), mouseY(384), rotates(false), truck(false),
orbit(false), ejecutandoOrbit(false), indOrbit(0), zOrbit(0) {
	x = 0.0;
	y = 80.0;
	z = -80.0;
	xLookAt = 0.0;
	yLookAt = 0.0;
	zLookAt = 0.0;
	fovY = 45.0f;
	ProjectionMatrix *= glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 2000.f);
	ViewMatrix *= glm::lookAt(glm::vec3(x, y, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
}

void PagCamera::mover(double movX, double movY, double movZ){
	if(!orbit) {
		x -= movX;
		xLookAt -= movX;
		y += movY;
		yLookAt += movY;
		if (truck) {
			zLookAt += movZ;
			z += movZ;
		}
		ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
			glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
	}
}

/**
* Funcion que engloba todos los movimientos, excepto el Orbit y el Zoom, que se pueden realizar con la Camera
*/
void PagCamera::girar(double movX, double movY) {
	if (!orbit) {
		if (rotates) {
			double xtemp = mouseX - movX;
			xtemp = xtemp / 2;
			mouseX = movX;
			xLookAt += xtemp;
			zLookAt -= xtemp;
			double ytemp = mouseY - movY;
			ytemp = ytemp / 2;
			yLookAt += ytemp;
			mouseY = movY;

			ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
				glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
		}else {
			mouseX = movX;
			mouseY = movY;
		}
	}else {
		mouseX = movX;
		mouseY = movY;
	}
}

/**
* Movimiento Orbit de la Camera
*/
void PagCamera::movOrbit() {
	if (!ejecutandoOrbit) {
		xLookAt = 0.0;
		yLookAt = 0.0;
		zLookAt = 0.0;
		ProjectionMatrix = glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 2000.f);
		ViewMatrix = glm::lookAt(glm::vec3(x, y, z),
			glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
		ejecutandoOrbit = true;
		zOrbit = z;
	}

	double angleRadIncrement = (2 * PI) / 100;

	x = zOrbit * cos(angleRadIncrement * (indOrbit % 100));
	z = zOrbit * -sin(angleRadIncrement * (indOrbit % 100));
	indOrbit++;
	ViewMatrix = glm::lookAt(glm::vec3(x, 30.0, z),
		glm::vec3(xLookAt, yLookAt, zLookAt), glm::vec3(0.0, 1.0, 0.0));
	sleep();
}

/**
* Funcion que resetea los valores por defecto de la Camera
*/
void PagCamera::resetCamera() {
	ejecutandoOrbit = false;
}

/**
* Movimiento Orbit de la Camera
*/
void PagCamera::zoom(double _zoom) {
	_zoom = _zoom / 50;
	if(fovY + _zoom >= 0.1) fovY += _zoom;
	ProjectionMatrix = glm::perspective(fovY, 4.0f / 3.0f, 0.1f, 2000.f);
}

PagCamera::~PagCamera() {}
