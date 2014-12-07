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

void Mesh::printstructure(const std::string& filename) {
  std::ofstream ofs;
  ofs.open(filename, std::ofstream::out );
  //~ for (unsigned long i=0;i < m_tri.size();i++) {
    //~ ofs << "sommet : "<< m_tri[i].e1->getVertex().getx()<< " " << m_tri[i].e1->getVertex().gety()<< " " << m_tri[i].e1->getVertex().getz(); 
    //~ ofs << "| image alpha0 : "<< m_tri[i].e1->alpha0()->getVertex().getx() << " "<< m_tri[i].e1->alpha0()->getVertex().gety()<<" " << m_tri[i].e1->alpha0()->getVertex().getz();  
    //~ ofs << "| image alpha1 : "<< m_tri[i].e1->alpha1()->getVertex().getx()<< " " << m_tri[i].e1->alpha1()->getVertex().gety()<< " " << m_tri[i].e1->alpha1()->getVertex().getz();
    //~ ofs << "| image alpha2 : "<< m_tri[i].e1->alpha2()->getVertex().getx()<< " " << m_tri[i].e1->alpha2()->getVertex().gety()<< " " << m_tri[i].e1->alpha2()->getVertex().getz()<<std::endl; 
  //~ }
  Edge* current = m_tri[0].e1;
  Edge* following = current;
  Edge* temp = current;  
  do {
    do {  
	ofs << "sommet : "<< following->getVertex().getx()<< " " << following->getVertex().gety()<< " " << following->getVertex().getz(); 
    ofs << "| image alpha0 : "<< following->alpha0()->getVertex().getx() << " "<< following->alpha0()->getVertex().gety()<<" " << following->alpha0()->getVertex().getz();  
    ofs << "| image alpha1 : "<< following->alpha1()->getVertex().getx()<< " " << following->alpha1()->getVertex().gety()<< " " << following->alpha1()->getVertex().getz();
    ofs << "| image alpha2 : "<< following->alpha2()->getVertex().getx()<< " " << following->alpha2()->getVertex().gety()<< " " << following->alpha2()->getVertex().getz()<<std::endl; 
    following = following->alpha0();
    }while (following != temp);
    following = following->alpha2();
    temp=following;
  }while (following != current);
}

int Mesh::load(const std::string& filename){
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

