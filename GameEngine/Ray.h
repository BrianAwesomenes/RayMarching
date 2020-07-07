#pragma once

#include "Vector.h"

class Ray
{
	Vector3 origin;

	int distance;

	Vector3 direction;
public:
	Ray(Vector3 origin = Vector3::zero, Vector3 direction = Vector3::zero);

	void march(int dist);

	Vector3 getOrigin();

	Vector3 getPoint();

	int getDistance();

	Vector3 getDirection();
};

