#include <iostream>
#include "Mesh.h"

using namespace std;

int main(int argc, char** argv) {
	int returnCode = 0;
    std::string filename;
    if(argc != 2){
		// Wrong command-line.
		std::cout << "USAGE: " << argv[0] << " objfile.obj" << std::endl;
		returnCode = -1;
		goto endOfProg;
	}    
	filename.assign(argv[1]);
	// An object is passed to the program. Let's process it !
	std::cout << "Loading mesh " << filename << "...";
	{
     Mesh m;
    	if(m.load(argv[1]) != MESH_LOADED){
	    	std::cout << "FAILED" << std::endl;
    		returnCode = -2;
	    	goto endOfProg;
    	}
    	std::cout << " loaded." << std::endl;
	
    	std::cout << "Vertices: " << m.getNbVertices() << std::endl;
    	std::cout << "Edges:    " << m.getNbEdges() << std::endl;
    	std::cout << "Faces:    " << m.getNbFaces() << std::endl;
	
    	std::cout << "Evaluating the Euler characteristic of " << filename << "... " << m.euler() << std::endl;
    	std::cout << "Evaluating the genus of " << filename << "... " << m.genre() << std::endl;
        m.printstructure("test.txt");
    }
endOfProg:
#ifndef WORKAROUND
	std::cout << "Press any key to quit..." << std::endl;
	std::cin.ignore();
#endif
	return returnCode;
}

