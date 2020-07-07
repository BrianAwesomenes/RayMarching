#include <iostream>
#include "Vector.h"
#include "Matrix.h"

using namespace std;

ostream& operator << (ostream& out, const Vector3 vec)
{
	out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';

	return out;
}

ostream& operator << (ostream& out, const Vector2 vec)
{
	out << '(' << vec.x << ", " << vec.y << ')';

	return out;
}

ostream& operator << (ostream& out, const Point3 vec)
{
	out << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';

	return out;
}

ostream& operator << (ostream& out, const Matrix4x4f mat)
{
	out << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << ' ' << mat[0][3] << endl;
	out << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << ' ' << mat[1][3] << endl;
	out << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << ' ' << mat[2][3] << endl;
	out << mat[3][0] << ' ' << mat[3][1] << ' ' << mat[3][2] << ' ' << mat[3][3] << endl;

	return out;
}

ostream& operator << (ostream& out, const Matrix4x4d mat)
{
	out << mat[0][0] << ' ' << mat[0][1] << ' ' << mat[0][2] << ' ' << mat[0][3] << endl;
	out << mat[1][0] << ' ' << mat[1][1] << ' ' << mat[1][2] << ' ' << mat[1][3] << endl;
	out << mat[2][0] << ' ' << mat[2][1] << ' ' << mat[2][2] << ' ' << mat[2][3] << endl;
	out << mat[3][0] << ' ' << mat[3][1] << ' ' << mat[3][2] << ' ' << mat[3][3] << endl;

	return out;
}