#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "Mesh.h"	

Mesh::Mesh():m_nbf(0), m_data(nullptr) {
}
Mesh::~Mesh() {
}

int Mesh::euler() {
  return vertexBuf.size() - m_nbEdge + m_nbf;
}

int Mesh::genre() {
  return 1 - (this->euler() + 1)/2;// 1 - (euler + nb composante_connexe (ici 1) + 0 (surface orientable))/2
}

int Mesh::load(const std::string& filename){
	std::ifstream ifs(filename);
	if(!ifs){
		return 1;
	}
	
	//std::vector<Vector3d> vertexBuf;
	
	std::string line;
	std::string head(2, '\0');
	float x, y, z;
	int s1, s2, s3;
	int curTriIndex = -1;
	
	while(getline(ifs, line)){
		if(line[0] != '#' && line[0] != 'o' && line[0] != 's'){
			if(line[0] == 'v'){
				// v 0.5 4.7 8.5
				sscanf(line.data(), "%s %f %f %f",const_cast<char*>(head.data()), &x, &y, &z);
				vertexBuf.emplace(vertexBuf.end(), x, y, z);
			}else if(line[0] == 'f'){
				// f 1 5 4
				sscanf(line.data(), "%s %d %d %d",const_cast<char*>(head.data()), &s1, &s2, &s3);
				vertexBuf.emplace(vertexBuf.end(), s1, s2, s3);
				++m_nbf;
				// Génération d'un triangle
				Triangle tri;
				tri.e1 = new Edge(vertexBuf[s1-1]);
				tri.e2 = new Edge(vertexBuf[s2-1]);
				tri.e3 = new Edge(vertexBuf[s3-1]);
				// Mise en place des relations next() et prev()
				// Dans le triangle
				tri.e1->connectTo0(tri.e2);
				tri.e2->connectTo0(tri.e3);
				tri.e3->connectTo0(tri.e1);
				m_tri.push_back(tri);
				++curTriIndex;
				// Lier les triangles entre eux
				for(int i = 0 ; i<curTriIndex; ++i){
					Triangle  curTri (m_tri[curTriIndex]);
					Triangle  oldTri  (m_tri[i]); 
					// test de correspondance des sommets
					if( (curTri.e1)->m_vertex == (oldTri.e1)->m_vertex){
						if( (curTri.e1)->alpha0() == (oldTri.e1)->alpha1()){
							curTri.e1->connectTo2(oldTri.e1);
							oldTri.e1->connectTo2(curTri.e1);
						}
					}
					
					if( (curTri.e2)->m_vertex == (oldTri.e2)->m_vertex){
						if(curTri.e2->alpha0() == oldTri.e2->alpha1()){
							curTri.e2->connectTo2(oldTri.e2);
							oldTri.e2->connectTo2(curTri.e2);
						}
					}
					
					if(curTri.e3->m_vertex == oldTri.e3->m_vertex){
						if(curTri.e3->alpha0() == oldTri.e3->alpha1()){
							curTri.e3->connectTo2(oldTri.e3);
							oldTri.e3->connectTo2(curTri.e3);
						}
					}
				}
			}
		}
	}
	ifs.close();
	m_nbEdge = vertexBuf.size()*1.5;
    return 0;
}

