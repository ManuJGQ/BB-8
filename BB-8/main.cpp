#include "PagRenderer.h"
#include "PagCamera.h"

PagRenderer escena;
PagCamera camera;

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
	camera.girar(xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		camera.setRotates(true);
		camera.setTruck(false);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) camera.setRotates(false);
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		camera.setTruck(true);
		camera.setRotates(false);
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) camera.setTruck(false);
}

void scroll(GLFWwindow* window, double x, double y) {
	camera.zoom(y * -1);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_O && action == GLFW_REPEAT) {
		camera.setOrbit(true);
		camera.movOrbit();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 ViewMatrix = camera.getViewMatrix();
		glm::mat4 ProjectionMatrix = camera.getProjectionMatrix();

		escena.pintarEscena(ViewMatrix, ProjectionMatrix);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	if (key == GLFW_KEY_O && action == GLFW_RELEASE) {
		camera.setOrbit(false);
		//camera.resetCamera();
	}
	if (key == GLFW_KEY_UP && action == GLFW_REPEAT) {
		if(camera.getTruck()) camera.mover(0.0, 0.0, 1.0);
		else camera.mover(0.0, 1.0, 0.0);
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT) {
		if (camera.getTruck())camera.mover(0.0, 0.0, -1.0);
		else camera.mover(0.0, -1.0, 0.0);
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT) {
		camera.mover(1.0, 0.0, 0.0);
	}
	if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT) {
		camera.mover(-1.0, 0.0, 0.0);
	}
}

int main(int argc, char** argv) {

	//Preparamos la ventana
	std::cout << "Starting application" << std::endl;

	if (!glfwInit()) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

	GLFWwindow* window;

	window = glfwCreateWindow(1024, 768, "PAG Practica 4 - TEXTURAS", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return -2;
	}

	glfwHideWindow(window);

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -3;
	}

	std::cout << glGetString(GL_RENDERER) << std::endl;
	std::cout << glGetString(GL_VENDOR) << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	//Inicializamos Camara
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	camera = PagCamera(x, y);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Callbacks Camara & Teclado
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll);
	glfwSetKeyCallback(window, key_callback);


	escena.cargarEscena();
	glfwShowWindow(window);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glViewport(0, 0, 1024, 768);

	glEnable(GL_DEPTH_TEST);

	//Dibujamos los objetos
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 ViewMatrix = camera.getViewMatrix();
		glm::mat4 ProjectionMatrix = camera.getProjectionMatrix();

		escena.pintarEscena(ViewMatrix, ProjectionMatrix);

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	return 0;
}
