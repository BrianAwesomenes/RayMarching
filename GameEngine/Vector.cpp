#include "Vector.h"
#include <math.h>

Vector3 Vector3::zero = Vector3();
Vector3 Vector3::one = Vector3(1, 1, 1);

Vector2 Vector2::zero = Vector2();
Vector2 Vector2::one = Vector2(1, 1);

Point3 Point3::zero = Point3();
Point3 Point3::one = Point3(1, 1, 1);

Vector3 Vector3::cross(Vector3 a, Vector3 b) {
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;

	return Vector3(x, y, z);
}

float Vector3::dot(Vector3 a, Vector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::cross(Vector3 b)
{
	return cross(*this, b);
}

float Vector3::dot(Vector3 b)
{
	return dot(*this, b);
}

float Vector3::magnitude() {
	return sqrtf(x*x + y*y + z*z);
}

Vector3 Vector3::getUnit() {
	float mag = magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}

void Vector3::normalize()
{
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}

Vector3 Vector3::normal()
{
	float mag = magnitude();
	return Vector3(x / mag, y / mag, z / mag);
}

Vector3 Vector3::operator+(Vector3 b) {
	return Vector3(x + b.x, y + b.y, z + b.z);
}

Vector3 Vector3::operator-(Vector3 b) {
	return Vector3(x - b.x, y - b.y, z - b.z);
}

Vector3 Vector3::operator*(float s) {
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(float s) {
	return Vector3(x / s, y / s, z / s);
}

Vector3::operator Point3() const {
	return Point3((int)x, (int)y, (int)z);
}

Vector3 operator*(float s, Vector3 v)
{
	return Vector3(v.x * s, v.y * s, v.z * s);
}
