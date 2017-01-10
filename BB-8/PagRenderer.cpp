#include "PagRenderer.h"

#include <iostream>
#include <string>

#include <set>

#include <algorithm>
#include "dirent.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"
#include <filesystem>

bool has_suffix(const std::string &str, const std::string &suffix) {
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

PagRenderer::PagRenderer(){

	//char* docdir = getenv("userprofile");
	//std::string path = docdir;
	//path += "/Desktop/";
	//std::string nombreFichero;

	////ARCHIVO GEOMETRIA

	//nombreFichero = path;
	//nombreFichero += "b3-in.txt";
	//std::ofstream ficheroGeom;
	//ficheroGeom.open(nombreFichero);
	//ficheroGeom << 13 << "," << 0 << std::endl;
	////for (float i = 0; i <= 12; i += 0.5) {
////	ficheroGeom << i << "," << -1 * sqrt((12 + i)*(12 - i)) << std::endl;
////}
	//for (float i = 12; i >= 0; i -= 0.5) {
	//	ficheroGeom << i << "," <<  40 + sqrt((12 + i)*(12 - i)) << std::endl;
	//}
	//ficheroGeom.close();

	// Leemos los datos y txt del usuario
	int perfiles = 8;
	/*std::cout << "Introduce el numero de perfiles" << std::endl;
std::cin >> perfiles;*/

	ficheros = new Structs::Fichero[perfiles];

	int j = perfiles;
	while (j != 0) {
		std::string archivo;
		if (j == 1)archivo = "b1-in.txt";
		if (j == 2)archivo = "b2-in.txt";
		if (j == 3)archivo = "b3-in.txt";
		if (j == 4)archivo = "b4-in.txt";
		if (j == 5)archivo = "b5-in.txt";
		if (j == 6)archivo = "b6-in.txt";
		if (j == 7)archivo = "b7-in.txt";
		if (j == 8)archivo = "b8-in.txt";
		/*std::cout << "Escriba el nombre del fichero " << perfiles - j + 1 << " (con .txt)" << std::endl;
	std::cin >> archivo;*/

		std::string _nTextura;
		/*std::cout << "Escriba la textura para " << archivo << " (sin .png)" << std::endl;
	std::cin >> _nTextura;*/

		if (j == 1)_nTextura = "bb8";
		if (j == 2)_nTextura = "bb8-c2";
		if (j == 3)_nTextura = "bb8-ca";
		if (j == 4)_nTextura = "bb8-ca-top";
		if (j == 5)_nTextura = "bb8-eye";
		if (j == 6)_nTextura = "bb8-eye";
		if (j == 7)_nTextura = "bb8-eye";
		if (j == 8)_nTextura = "bb8-eye";


		std::string _nBump;
		/*std::cout << "Escriba la textura para " << archivo << " (sin .png)" << std::endl;
	std::cin >> _nTextura;*/

		if (j == 1)_nBump = "bump1e";
		if (j == 2)_nBump = "bump3";
		if (j == 3)_nBump = "bump2b";
		if (j == 4)_nBump = "bump3";
		if (j == 5)_nBump = "bump3";
		if (j == 6)_nBump = "bump3";
		if (j == 7)_nBump = "bump3";
		if (j == 8)_nBump = "bump3";


		Structs::Fichero _fichero;
		_fichero.nombreAlumno = archivo;
		_fichero.archivoIN = archivo;
		_fichero.nTextura = _nTextura;
		_fichero.nBump = _nBump;
		ficheros[perfiles - j] = _fichero;
		j--;
	}

	int slices = 100;
	/*std::cout << "Escriba el numero de slices" << std::endl;
std::cin >> slices;*/

	for (int i = 0; i < perfiles; i++) { ficheros[i].numSlices = slices; }

	//Creamos la jerarquia de objetos
	objects = Pag3DGroup(ficheros, perfiles);
}

void PagRenderer::cargarEscena() {
	//Cargamos las luces
	lights.push_back(PagLight(glm::vec3(-30.0, 30.0, -50.0), glm::vec3(0.46, -0.46, 0.75), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), 20.0f, 5.0f, 50.0f));
	//lights.push_back(PagLight(glm::vec3(0.0, 40.0, 80.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	//lights.push_back(PagLight(glm::vec3(-80.0, 40.0, -80.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	//lights.push_back(PagLight(glm::vec3(80.0, 40.0, -80.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	//lights.push_back(PagLight(glm::vec3(-80.0, 20.0, 0.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	//lights.push_back(PagLight(glm::vec3(0.0, 20.0, 80.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));

	//Creamos las Geometrias y Topologias de los diferentes objetos que componen la escena
	objects.createObject();

	glm::mat4 ModelMatrix(1.0);

	ModelMatrix *= glm::translate(glm::mat4(), glm::vec3(-8.0f, 45.7f, -8.9f));

	ModelMatrix *= glm::rotate(glm::mat4(1.0f), 0.70f, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix *= glm::rotate(glm::mat4(), -1.22f, glm::vec3(1.0f, 0.0f, 0.0f));

	ModelMatrix *= glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f));

	objects.setModelMatrix(ModelMatrix, 5);

	glm::mat4 ModelMatrix2(1.0);

	ModelMatrix2 *= glm::translate(glm::mat4(), glm::vec3(-1.1f, 48.0f, -10.0f));

	ModelMatrix2 *= glm::rotate(glm::mat4(1.0f), 0.08f, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix2 *= glm::rotate(glm::mat4(), -1.05f, glm::vec3(1.0f, 0.0f, 0.0f));

	ModelMatrix2 *= glm::translate(glm::mat4(), glm::vec3(0.0f, -2.0f, 0.0f));

	objects.setModelMatrix(ModelMatrix2, 6);

	glm::mat4 ModelMatrix3(1.0);

	ModelMatrix3 *= glm::translate(glm::mat4(), glm::vec3(-2.0f, -0.5f, 2.0f));

	objects.setModelMatrix(ModelMatrix3, 8);

	//Cargamos todas las Texturas del directorio Textures

	DIR *dir = opendir("Textures/");

	dirent *entry;
	while ((entry = readdir(dir)) != nullptr) {
		if (has_suffix(entry->d_name, ".png")) {

			std::string name = std::string(entry->d_name);
			int ind = name.find_last_of(".");
			std::string nombreSinExt = name.substr(0, ind);
			std::string path = "Textures/" + name;

			textures.insert_or_assign(nombreSinExt, PagTexture(path, GLuint(textures.size())));
		}
	}
	closedir(dir);

	//Cargamos todos los shaders
	std::vector<std::string> nombreShaders;

	DIR *dirS = opendir("Textures/..");

	dirent *entryS;

	std::set<std::string> shadersNames;

	while ((entryS = readdir(dirS)) != nullptr) {
		if (has_suffix(entryS->d_name, ".frag")) {

			//std::cout << entryS->d_name << std::endl;

			entryS = readdir(dirS);

			if (has_suffix(entryS->d_name, ".vert")) {

				//std::cout << entryS->d_name << std::endl;

				std::string name = std::string(entryS->d_name);
				int ind = name.find_last_of(".");
				name = name.substr(0, ind);

				ind = name.find_last_of("-");
				std::string name2 = name.substr(0, ind);


				if (shadersNames.find(name2) == shadersNames.end()) {
					nombreShaders.push_back(name2);
					std::cout << "[" << nombreShaders.size() - 1 << "] - " << name2 << std::endl;
					shadersNames.insert(name2);
				}

			}

		}
	}
	closedir(dirS);

	int s;
	std::cout << "Escoja el nº del shader a usar: ";
	std::cin >> s;

	nombreShader = nombreShaders[s];

	if (nombreShader == "Texture" || nombreShader == "ADS" || nombreShader == "Bump" || nombreShader == "Shadow") {
		for (int i = 0; i < lights.size(); i++) {
			std::string name = nombreShader + "-";
			char l = lights[i].light;
			name += l;
			PagShaderProgram* shader = new PagShaderProgram();
			shader->createShaderProgram(name.c_str());
			shadersUtilizados.push_back(std::pair<std::string, PagShaderProgram*>(name, shader));
			lights[i].crearFBOShadowsMap(i, textures.size() + i);
		}
		if(nombreShader == "Bump") {
			nombreShader = "Texture";
			for (int i = 0; i < lights.size(); i++) {
				std::string name = nombreShader + "-";
				char l = lights[i].light;
				name += l;
				PagShaderProgram* shader = new PagShaderProgram();
				shader->createShaderProgram(name.c_str());
				shadersUtilizadosAux.push_back(std::pair<std::string, PagShaderProgram*>(name, shader));
			}
			nombreShader = "Bump";
		}
		if (nombreShader == "Shadow") {
			std::string name = nombreShader + "-Inicio";
			PagShaderProgram* shader = new PagShaderProgram();
			shader->createShaderProgram(name.c_str());
			shadersUtilizados.push_back(std::pair<std::string, PagShaderProgram*>(name, shader));
		}
	}
}

void PagRenderer::pintarEscena(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix) {

	if (nombreShader == "Texture" || nombreShader == "ADS" || nombreShader == "Bump") {

		glEnable(GLenum(GL_BLEND));
		glDepthFunc(GLenum(GL_LEQUAL));

		for (int i = 0; i < lights.size(); i++) {

			if (i == 0) { glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); }
			else { glBlendFunc(GL_SRC_ALPHA, GL_ONE); }

			objects.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[i], &lights[i], i);

		}
	}
	else if (nombreShader == "Shadow") {

		for (int i = 0; i < lights.size(); i++) {
			if (lights[i].needRecalcShadows) {
	
				glBindFramebuffer(GL_FRAMEBUFFER, lights[i].shadowFBO);
				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, lights[i].depthTex);
				glClear(GL_DEPTH_BUFFER_BIT);
				glViewport(0, 0, lights[i].shadowMapWidth, lights[i].shadowMapHeight);
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_LESS);
				glPrimitiveRestartIndex(0xFFFF);
				glEnable(GL_PRIMITIVE_RESTART);
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);

				objects.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[lights.size()], NULL, lights.size());

				lights[i].needRecalcShadows = false;
			}
		}

		glClearColor(1.0, 1.0, 1.0, 1.0);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glPrimitiveRestartIndex(0xFFFF);
		glEnable(GL_PRIMITIVE_RESTART);
		glEnable(GL_BLEND);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glViewport(0, 0, 1024, 768);
		shadowBias = glm::mat4(0.5, 0.0, 0.0, 0.0,
							   0.0, 0.5, 0.0, 0.0,
							   0.0, 0.0, 0.5, 0.0,
							   0.5, 0.5, 0.5, 1.0);
		glDepthFunc(GL_LEQUAL);
		bool firsLight = true;

		for (int i = 0; i < lights.size(); i++) {

			if (firsLight){
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				firsLight = false;
			}
			else {
				glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			}

			depthTex = lights[i].depthTex;
			objects.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[i], &lights[i], i);
			std::cout << "PINTO" << std::endl;

		}
	}
	else {
		objects.draw(ViewMatrix, ProjectionMatrix, this, shadersUtilizados[0], NULL, 0);
	}

}

PagRenderer::~PagRenderer() {
	delete[] ficheros;
}
