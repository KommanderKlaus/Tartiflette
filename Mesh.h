#ifndef MESH_H
#define	MESH_H

#include <iostream>
#include <string>
#include <vector>
#include "Edge.h"

#define MESH_LOAD_FAILED 0
#define MESH_LOADED 1

class Mesh {
public:
	Mesh();
	~Mesh();
    int genre();
	int euler();
	int load(const std::string& filename);
    int printstructure(const std::string& filename);	
	int getNbVertices();
	int getNbEdges();
	int getNbFaces();
private:
    int printstructure(const std::string& filename, Edge* E1);
    int m_nbEdge,m_nbf;
    std::vector<Vector3d> m_vertexBuf;
	std::vector<Triangle> m_tri;
};

#endif	/* MESH_H */

