#ifndef VECTOR_H
#define	VECTOR_H

struct Vector3d {
	/**
	 * Default constructor
     */
	Vector3d();
	
	/**
	 * Constructs a 3d vector with its coordinates
     * @param x
     * @param y
     * @param z
     */
	Vector3d(float x, float y, float z);
	
	/**
	 * Copy constructor
     * @param o : the object to be copied
     */
	Vector3d(const Vector3d& o) = default;
	
	/**
	 * Move constructor
     * @param o : the object to be moved
     */
	Vector3d(Vector3d&& o) = default;
	
	/**
	 * Destructor
     */
	~Vector3d() = default;
	
	/**
	 * Assignation operator
     * @param o
     * @return 
     */
	Vector3d& operator=(const Vector3d& o);
	
	/**
	 * Coordinates of the 3d vector
	 */
	float x,y,z;
};

/**
 * Comparison between two 3d vectors.
 * @param a : first operand
 * @param b : second operand
 * @return true if vectors are equals, otherwise it's false
 */
bool operator==(const Vector3d& a, const Vector3d& b);

#endif	/* VECTOR_H */

