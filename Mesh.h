#ifndef MESH_H
#define	MESH_H

#include <iostream>
#include <string>
#include <vector>
#include "Edge.h"

class Mesh {
public:
	Mesh();
	~Mesh();
    int genre();
	int euler();
	int load(const std::string& filename);
private:
    int m_nbEdge,m_nbf;
    std::vector<Vector3d> vertexBuf;
	Edge * find(const Vector3d& v);
	std::vector<Triangle> m_tri;
	MeshData * m_data;
};

std::ostream& operator<<(std::ostream& os, const Mesh& m);

#endif	/* MESH_H */

