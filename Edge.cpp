#include <string.h> // memcpy, memset
#include "Edge.h"
#include <fstream>
#include <vector>
#include <stdio.h>

Edge::Edge():
m_vertex(0.0f, 0.0f, 0.0f){
	memset(m_neighbor, 0, sizeof(m_neighbor));
}

Edge::Edge(const Vector3d& vertex, Edge * a0, Edge * a1, Edge * a2):
m_vertex(vertex)
{
	m_neighbor[0] = a0;
	m_neighbor[1] = a1;
	m_neighbor[2] = a2;
}

Edge::Edge(const Vector3d& vertex):
m_vertex(vertex){
	memset(m_neighbor, 0, sizeof(m_neighbor));
}

Edge::~Edge() {
}

Edge& Edge::operator=(const Edge& o) {
	this->m_vertex = o.m_vertex;
	memcpy(m_neighbor, o.m_neighbor, sizeof(m_neighbor));
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
	this->m_neighbor[0] = a0;	// Next of *this set to a0
	a0->  m_neighbor[1] = this;	// Previous of a0 set to *this
}

void Edge::connectTo1(Edge* a1) {
	this->m_neighbor[1] = a1;// Previous of *this set to a0
	a1->  m_neighbor[0] = this;	// Next of a0 set to *this
}

void Edge::connectTo2(Edge* a2) {
	this->m_neighbor[2] = a2;// Opposite of *this set to a0
	a2->  m_neighbor[2] = this;	// Opposite of a0 set to *this
}
