#include "PagRenderer.h"

#include <iostream>
#include <string>

#include <set>

#include <algorithm>
#include "dirent.h"

#include <GL/glew.h> //glew SIEMPRE va antes del glfw
#include <GLFW/glfw3.h>
#include "gtc\matrix_transform.hpp"

bool has_suffix(const std::string &str, const std::string &suffix) {
	return str.size() >= suffix.size() &&
		str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

PagRenderer::PagRenderer() {

	//char* docdir = getenv("userprofile");
	//std::string path = docdir;
	//path += "/Desktop/";
	//std::string nombreFichero;

	////ARCHIVO GEOMETRIA

	//nombreFichero = path;
	//nombreFichero += "b-in.txt";
	//std::ofstream ficheroGeom;
	//ficheroGeom.open(nombreFichero);
	//ficheroGeom << 42 << "," << 0 << std::endl;
	//for (float i = 0; i <= 20; i += 0.5) {
	//	ficheroGeom << i << "," << -1 * sqrt((20 + i)*(20 - i)) << std::endl;
	//}
	//for (float i = 20; i >= 0; i -= 0.5) {
	//	ficheroGeom << i << "," <<  sqrt((20 + i)*(20 - i)) << std::endl;
	//}
	//ficheroGeom.close();

	// Leemos los datos y txt del usuario
	int perfiles;
	std::cout << "Introduce el numero de perfiles" << std::endl;
	std::cin >> perfiles;

	ficheros = new Structs::Fichero[perfiles];

	int j = perfiles;
	while (j != 0) {
		char* docdir = getenv("userprofile");
		std::string path = docdir;
		std::string archivo;
		path += "/Desktop/";
		std::cout << "Escriba el nombre del fichero " << perfiles - j + 1 << " (con .txt)" << std::endl;
		std::cin >> archivo;
		path += archivo;

		std::string _nTextura;
		std::cout << "Escriba la textura para " << archivo << " (sin .png)" << std::endl;
		std::cin >> _nTextura;

		Structs::Fichero _fichero;
		_fichero.nombreAlumno = archivo;
		_fichero.archivoIN = path;
		_fichero.nTextura = _nTextura;
		ficheros[perfiles - j] = _fichero;
		j--;
	}

	int slices;
	std::cout << "Escriba el numero de slices" << std::endl;
	std::cin >> slices;

	for (int i = 0; i < perfiles; i++) {
		ficheros[i].numSlices = slices;
	}

	//Creamos la jerarquia de objetos
	objects = Pag3DGroup(ficheros, perfiles);
}

void PagRenderer::cargarEscena() {
	//Cargamos las luces
	lights.push_back(PagLight(glm::vec3(0.0, 80.0, 0.0), 0.2f, 0.5f, 0.3f, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	lights.push_back(PagLight(glm::vec3(-60.0, 0.0, 60.0), 0.1f, 0.25f, 0.15f, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));
	lights.push_back(PagLight(glm::vec3(-60.0, 60.0, 100.0), 0.05f, 0.125f, 0.75f, glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0), 'P', 50.0f));

	//Creamos las Geometrias y Topologias de los diferentes objetos que componen la escena
	objects.createObject();

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

				PagShaderProgram *shader = new PagShaderProgram();

				shader->createShaderProgram(name.c_str());

				shaders.insert_or_assign(name, shader);

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
}

void PagRenderer::pintarEscena(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix) {
	for (int i = 0; i < lights.size(); i++) {
		objects.draw(ViewMatrix, ProjectionMatrix, this, &lights[i]);
	}
}

PagRenderer::~PagRenderer() {
	delete[] ficheros;
}
