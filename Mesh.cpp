#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <cmath>
#include "Mesh.h"	

Mesh::Mesh():
m_nbEdge(0),
m_nbf(0),
m_tri()
{}

Mesh::~Mesh() {
}

int Mesh::euler() {
    return m_vertexBuf.size() - m_nbEdge + m_nbf;
}

int Mesh::genre() {
  return 1- (this->euler() + 0 + 0)/2;// 1 - (euler + nb composante_connexe du bord (ici 0) + 0 (surface orientable))/2
}

int Mesh::printstructure(const std::string& filename) {
  std::ofstream ofs;
  ofs.open(filename, std::ofstream::out );
  Edge* E1 = m_tri[0].e1;
 // Edge* temp = following;  
	int i =0;
	for(;i<3;i++) {
		E1->IsVisited(true);
		ofs << "Edge : "<< E1->getVertex().getx()<< " " << E1->getVertex().gety()<< " " << E1->getVertex().getz(); 
	}
	if(E1->alpha2()->WasVisited() && E1->alpha0()->alpha2()->WasVisited() && E1->alpha0()->alpha0()->alpha2()->WasVisited()) {
		return 0;
	} 
	 if (!E1->alpha2()->WasVisited()) {
		printstructure(filename,E1->alpha2());
	 } 
	 if (!E1->alpha0()->alpha2()->WasVisited()) {
		 printstructure(filename,E1->alpha0()->alpha2());
	 }
	 if (!E1->alpha0()->alpha0()->alpha2()->WasVisited()) {
		 printstructure(filename,E1->alpha0()->alpha0()->alpha2());
	 }
}
int Mesh::printstructure(const std::string& filename, Edge* E1) 
{
	std::ofstream ofs;
    ofs.open(filename, std::ofstream::out );
	int i =0;
	for(;i<3;i++) {
		E1->IsVisited(true);
		ofs << "Edge : "<< E1->getVertex().getx()<< " " << E1->getVertex().gety()<< " " << E1->getVertex().getz(); 
	}
	if(E1->alpha2()->WasVisited() && E1->alpha0()->alpha2()->WasVisited() && E1->alpha0()->alpha0()->alpha2()->WasVisited()) {
		return 0;
	} 
	 if (!E1->alpha2()->WasVisited()) {
		printstructure(filename,E1->alpha2());
	 } 
	 if (!E1->alpha0()->alpha2()->WasVisited()) {
		 printstructure(filename,E1->alpha0()->alpha2());
	 }
	 if (!E1->alpha0()->alpha0()->alpha2()->WasVisited()) {
		 printstructure(filename,E1->alpha0()->alpha0()->alpha2());
	 }
}
int Mesh::load(const std::string& filename) {
	std::ifstream ifs(filename);
	if(!ifs){
		return MESH_LOAD_FAILED;
	}
	
	std::string line;
	std::string head(2, '\0');
	float x, y, z;
	int s1(-1), s2(-1), s3(-1);
	int curTriIndex = -1;
	
	while(getline(ifs, line)){
		if(line[0] == '#' || line[0] == 'o' || line[0] == 's'){
			continue;
		}
		if(line[0] == 'v'){
			// v 0.5 4.7 8.5
			sscanf(line.data(), "%s %f %f %f",const_cast<char*>(head.data()), &x, &y, &z);
			m_vertexBuf.emplace(m_vertexBuf.end(), x, y, z);
		}else if(line[0] == 'f'){
			// f 1 5 4
			sscanf(line.data(), "%s %d %d %d",const_cast<char*>(head.data()), &s1, &s2, &s3);
			//vertexBuf.emplace(vertexBuf.end(), s1, s2, s3);
			++m_nbf;
			// Génération d'un triangle
			m_tri.emplace_back(	new Edge(m_vertexBuf[s1-1]),
								new Edge(m_vertexBuf[s2-1]),
								new Edge(m_vertexBuf[s3-1]));
			++curTriIndex;
			// Link Triangles
			for(int i = 0 ; i<curTriIndex; ++i){
				Triangle& curTri (m_tri[curTriIndex]);
				Triangle& oldTri  (m_tri[i]); 
				// Matching test
				if(curTri.e1->getVertex() == oldTri.e1->getVertex()){
					curTri.e1->connectTo2(oldTri.e1);
				}else if(curTri.e1->getVertex() == oldTri.e2->getVertex()){
					curTri.e1->connectTo2(oldTri.e2);
				}else if(curTri.e1->getVertex() == oldTri.e3->getVertex()){
					curTri.e1->connectTo2(oldTri.e3);
				}
				
				if(curTri.e2->getVertex() == oldTri.e1->getVertex()){
					curTri.e2->connectTo2(oldTri.e1);
				}else if(curTri.e2->getVertex() == oldTri.e2->getVertex()){
					curTri.e2->connectTo2(oldTri.e2);
				}else if(curTri.e2->getVertex() == oldTri.e3->getVertex()){
					curTri.e2->connectTo2(oldTri.e3);
				}
				
				if(curTri.e3->getVertex() == oldTri.e1->getVertex()){
					curTri.e3->connectTo2(oldTri.e1);
				}else if(curTri.e3->getVertex() == oldTri.e2->getVertex()){
					curTri.e3->connectTo2(oldTri.e2);
				}else if(curTri.e3->getVertex() == oldTri.e3->getVertex()){
					curTri.e3->connectTo2(oldTri.e3);
				}
			}
		}else{
			// Unknown header. The file might be corrupted.
			// Flushing the mesh then return.
			m_nbEdge = 0;
			m_nbf = 0;
			m_tri.clear();
			m_vertexBuf.clear();
			return MESH_LOAD_FAILED;
		}
	}
	ifs.close();
	m_nbEdge = m_tri.size()*3/2;
    return MESH_LOADED;
}

int Mesh::getNbEdges() {
	return m_nbEdge;
}

int Mesh::getNbFaces() {
	return m_nbf;
}

int Mesh::getNbVertices() {
	return m_vertexBuf.size();
}

