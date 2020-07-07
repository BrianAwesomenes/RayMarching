#include "Ray.h"

Ray::Ray(Vector3 origin, Vector3 direction) : origin(origin), direction(direction), distance(0) {
	this->direction.normalize();
}

void Ray::march(int dist) {
	distance += dist;
}

Vector3 Ray::getOrigin() {
	return origin;
}

Vector3 Ray::getPoint() {
	return origin + direction * distance;
}

int Ray::getDistance() {
	return distance;
}

Vector3 Ray::getDirection()
{
	return direction;
}
