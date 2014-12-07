#ifndef EDGE_H
#define	EDGE_H

#include <exception>
#include "Vector.h"

struct Triangle;
class Mesh;

class Edge {
public:
	/**
	 * Default constructor
     */
	Edge();
	
	/**
	 * Copy constructor defaulted because we need the pointers, not the pointed data.
     * @param o : The Edge about to be copied
     */
	Edge(const Edge& o) = default;
	
	/**
	 * Construct a single Edge with a vertex
     * @param vertex
     */
	Edge(const Vector3d& vertex);
	
	/**
	 * Construct an Edge
     * @param vertex : The vertex associated to the edge
     * @param a0 : A pointer to the next Edge
     * @param a1 : A pointer to the previous Edge
     * @param a2 : A pointer to the opposite Edge
     */
	Edge(const Vector3d& vertex, Edge * a0, Edge * a1, Edge * a2);
	
	/**
	 * Move constructor deleted because it is nonsense
     * @param o : Edge to be moved
     */
	Edge(Edge&& o) = delete;
	
	/**
	 * Destroy an Edge without freeing neighbor pointers
     */
	~Edge() = default;

	/**
	 * Assignation operator
     * @param o
     * @return *this
     */
	Edge& operator=(const Edge& o);
	
	/**
	 * This method returns the next Edge
     * @return the next Edge
     */
	Edge * alpha0() const;
	
	/**
	 * This method returns the previous Edge
     * @return the previous Edge
     */
	Edge * alpha1() const;
	
	/**
	 * This method returns the opposite Edge
     * @return the opposite Edge
     */
	Edge * alpha2() const;
	
    /**
     * This method return vertices bind
     * to an Edge
     * **/
inline Vector3d getVertex() const {
	if(!m_pVertex) throw std::exception();
    return *(this->m_pVertex);
}
inline Edge* getNeighbor(int i) const {
      return m_neighbor[i];
}
	friend Mesh;
	friend Triangle;
private:
	/**
	 * Connects the current Edge to the next Edge
     * @param a0 the next Edge
     */
	void connectTo0(Edge * a0);
	
	/**
	 * Connects the current Edge to the previous Edge
     * @param a1 the previous Edge
     */
	void connectTo1(Edge * a1);
	
	/**
	 * Connects the current Edge to the opposite Edge
     * @param a2 the opposite Edge
     */
	void connectTo2(Edge * a2);
	
	/**
	 * This is the vertex associated to the edge
	 */
	const Vector3d * m_pVertex;
	
	/**
	 * This is the three neighbors of the current Edge
	 */
	Edge * m_neighbor[3];
};

struct Triangle{
	Edge * e1;
	Edge * e2;
	Edge * e3;
	Triangle ();
	Triangle (Edge * _e1, Edge * _e2, Edge * _e3);
	Triangle (const Triangle &tr) = delete;
	Triangle (Triangle&& tr);
	~Triangle();
	Triangle& operator=(const Triangle& o);
};

typedef Edge MeshData;

bool operator== (Edge& E1, Edge& E2);

#endif	/* EDGE_H */

