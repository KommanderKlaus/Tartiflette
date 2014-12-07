#include "Vector.h"

Vector3d::Vector3d():
x(0.0f),y(0.0f),z(0.0f)
{}

Vector3d::Vector3d(float x, float y, float z):
x(x),y(y),z(z)
{}

Vector3d& Vector3d::operator=(const Vector3d& o) {
	this->x = o.x;
	this->y = o.y;
	this->z = o.z;
    return *this;
}

float Vector3d::getx() const {
    return x;
}
float Vector3d::gety() const {
    return y;
}
float Vector3d::getz() const {
    return z;
}
bool operator==(const Vector3d& a, const Vector3d& b){
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
