#include <iostream>
#include "Mesh.h"

using namespace std;

void returnProc(){
#ifndef WORKAROUND
	std::cout << "Press any key to quit..." << std::endl;
	std::cin.ignore();
#endif
}

int main(int argc, char** argv) {
    std::string filename;
    if(argc != 2){
		// Wrong command-line.
		std::cout << "USAGE: " << argv[0] << " objfile.obj" << std::endl;
		returnProc();
		return -1;
	}    
	filename = argv[1];
	// An object is passed to the program. Let's process it !
	std::cout << "Loading mesh " << filename << "...";
	Mesh m;
	if(m.load(filename) != MESH_LOADED){
		std::cout << "FAILED" << std::endl;
		returnProc();
		return -2;
	}
	std::cout << " loaded." << std::endl;

	std::cout << "Vertices: " << m.getNbVertices() << std::endl;
	std::cout << "Edges:    " << m.getNbEdges() << std::endl;
	std::cout << "Faces:    " << m.getNbFaces() << std::endl;

	std::cout << "Evaluating the Euler characteristic of " << filename << "... " << m.euler() << std::endl;
	std::cout << "Evaluating the genus of " << filename << "... " << m.genre() << std::endl;
	// Formatting the ouput file
	std::string outFile = filename.substr(0, filename.find(".obj")) + ".topo";
	m.printstructure(outFile);
	returnProc();
	return 0;
}

