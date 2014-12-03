#include "Edge.h"
#include <fstream>
#include <vector>
#include <stdio.h>

Edge::Edge(const Vector3d& vertex, Edge * a0, Edge * a1, Edge * a2):
m_vertex(vertex)
{
	m_neighbor[0] = a0;
	m_neighbor[1] = a1;
	m_neighbor[2] = a2;
}

Edge::~Edge() {
}

Edge* Edge::alpha0() const{
	return m_neighbor[0];
}

Edge* Edge::alpha1() const{
	return m_neighbor[1];
}

Edge* Edge::alpha2() const{
	return m_neighbor[2];
}

void Edge::connectTo0(Edge* a0) {
	m_neighbor[0] = a0;
}

void Edge::connectTo1(Edge* a1) {
	m_neighbor[1] = a1;
}

void Edge::connectTo2(Edge* a2) {
	m_neighbor[2] = a2;
}

bool operator==(const Triangle& t1, const Triangle& t2){
	return (t1.e1 == t2.e1 &&t1.e2 == t2.e2 &&t1.e3 == t2.e3);
}
