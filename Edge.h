#ifndef EDGE_H
#define	EDGE_H

#include "Vector.h"

class Mesh;

class Edge {
public:
	Edge(const Vector3d& vertex, Edge * a0 = nullptr, Edge * a1 = nullptr, Edge * a2 = nullptr);
	~Edge();

	Edge * alpha0() const;	// next
	Edge * alpha1() const;	// prev
	Edge * alpha2() const;	// opposite
	
	friend Mesh;
private:
	void connectTo0(Edge * a0);
	void connectTo1(Edge * a1);
	void connectTo2(Edge * a2);
	
	Vector3d m_vertex;
	Edge * m_neighbor[3];
};

struct Triangle{
	Edge * e1;
	Edge * e2;
	Edge * e3;
	Triangle () {
		e1= nullptr;
		e2= nullptr;
		e3= nullptr;
	};
	Triangle (const Triangle &tr) {
		e1 = tr.e1;
		e2 = tr.e2;
		e3 = tr.e3;
	};
};

bool operator==(const Triangle& t2, const Triangle& t411);

typedef Edge MeshData;

#endif	/* EDGE_H */

