#include "Vector.h"

bool operator==(const Vector3d& a, const Vector3d& b){
	return a.x == b.x && a.y == b.y && a.z == b.z;
}
