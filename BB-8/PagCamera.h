#pragma once

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

#include <windows.h>

class PagCamera{
	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	
	double x;
	double y;
	double z;

	double xLookAt;
	double yLookAt;
	double zLookAt;

	float fovY;

	double mouseX;
	double mouseY;

	bool rotates;
	bool truck;
	bool orbit;
	bool ejecutandoOrbit;

	int indOrbit;
	double zOrbit;
public:
	PagCamera();
	PagCamera(double x, double y);
	void mover(double movX, double movY);
	void movOrbit();
	void resetCamera();
	static void sleep() { Sleep(100); }
	glm::mat4 getViewMatrix() const { return ViewMatrix; }
	glm::mat4 getProjectionMatrix() const { return ProjectionMatrix; }
	void setRotates(bool _rotates) { rotates = _rotates; }
	void setTruck(bool _truck) { truck = _truck; }
	void setOrbit(bool _orbit) { orbit = _orbit; }
	bool getOrbit() const { return orbit; }
	void zoom(double _zoom);

	~PagCamera();
};

