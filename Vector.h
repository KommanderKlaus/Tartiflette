#ifndef VECTOR_H
#define	VECTOR_H

struct Vector3d {
	Vector3d(float __x, float __y, float __z):x(__x),y(__y),z(__z){}
	Vector3d(const Vector3d& o){
		this->x = o.x;
		this->y = o.y;
		this->z = o.z;
	}
	float x,y,z;
};

bool operator==(const Vector3d& a, const Vector3d& b);

#endif	/* VECTOR_H */

