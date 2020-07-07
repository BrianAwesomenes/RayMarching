#include "Matrix.h"
#include <algorithm>

#define v(r, c) values[4 * r + c]
#define Deg2Rad 0.0174532925

const Matrix4x4f Matrix4x4f::identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
};

const Matrix4x4d Matrix4x4d::identity = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
};

Matrix4x4f::Matrix4x4f()
{
	std::fill(values, values + 16, 0);
}

Matrix4x4f::Matrix4x4f(const float values[16])
{
#define op(r, c) this->v(r, c) = v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()
}

Matrix4x4f::Matrix4x4f(float a00, float a01, float a02, float a03, float a10, float a11, float a12, float a13, float a20, float a21, float a22, float a23, float a30, float a31, float a32, float a33)
{
	v(0, 0) = a00; v(0, 1) = a01; v(0, 2) = a02; v(0, 3) = a03;
	v(1, 0) = a10; v(1, 1) = a11; v(1, 2) = a12; v(1, 3) = a13;
	v(2, 0) = a20; v(2, 1) = a21; v(2, 2) = a22; v(2, 3) = a23;
	v(3, 0) = a30; v(3, 1) = a31; v(3, 2) = a32; v(3, 3) = a33;
}

Matrix4x4f& Matrix4x4f::operator=(const Matrix4x4f& b)
{
#define op(r, c) v(r, c) = b.v(r, c)
	/*Operation*/{op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3);}
#undef op()

	return *this;
}

Matrix4x4f& Matrix4x4f::operator=(const float values[16])
{
#define op(r, c) this->v(r, c) = v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return *this;
}

float* Matrix4x4f::operator[](int row)
{
	return values + 4 * row;
}

const float* Matrix4x4f::operator[](int row) const
{

	return values + 4 * row;
}

float Matrix4x4f::det()
{
	//Precaclulate stuff that gets used multiple times
	float sub[6];
	sub[0] = (v(2, 2) * v(3, 3)) - (v(3, 2) * v(2, 3));
	sub[1] = (v(2, 1) * v(3, 3)) - (v(3, 1) * v(2, 3));
	sub[2] = (v(2, 1) * v(3, 2)) - (v(3, 1) * v(2, 2));
	sub[3] = (v(2, 0) * v(3, 3)) - (v(3, 0) * v(2, 3));
	sub[4] = (v(2, 0) * v(3, 2)) - (v(3, 0) * v(2, 2));
	sub[5] = (v(2, 0) * v(3, 1)) - (v(3, 0) * v(2, 1));

	//I wrote a python script to spit this out. Sorry for the cancer I didn't want any recursion.
	return v(0, 0) * (v(1, 1) * (sub[0]) - v(1, 2) * (sub[1]) + v(1, 3) * (sub[2])) - v(0, 1) * (v(1, 0) * (sub[0]) - v(1, 2) * (sub[3]) + v(1, 3) * (sub[4])) + v(0, 2) * (v(1, 0) * (sub[1]) - v(1, 1) * (sub[3]) + v(1, 3) * (sub[5])) - v(0, 3) * (v(1, 0) * (sub[2]) - v(1, 1) * (sub[4]) + v(1, 2) * (sub[5]));
}

void Matrix4x4f::invert()
{
	float det = Matrix4x4f::det();

	if (det == 0)
		return;

	Matrix4x4f temp;

	//Precaclulate stuff that gets used multiple times
	float sub[18];
	sub[0] = (v(2, 2) * v(3, 3)) - (v(3, 2) * v(2, 3));
	sub[1] = (v(2, 1) * v(3, 3)) - (v(3, 1) * v(2, 3));
	sub[2] = (v(2, 1) * v(3, 2)) - (v(3, 1) * v(2, 2));
	sub[3] = (v(2, 0) * v(3, 3)) - (v(3, 0) * v(2, 3));
	sub[4] = (v(2, 0) * v(3, 2)) - (v(3, 0) * v(2, 2));
	sub[5] = (v(2, 0) * v(3, 1)) - (v(3, 0) * v(2, 1));

	sub[6] = (v(1, 2) * v(3, 3)) - (v(3, 2) * v(1, 3));
	sub[7] = (v(1, 1) * v(3, 3)) - (v(3, 1) * v(1, 3));
	sub[8] = (v(1, 1) * v(3, 2)) - (v(3, 1) * v(1, 2));
	sub[9] = (v(1, 0) * v(3, 3)) - (v(3, 0) * v(1, 3));
	sub[10] = (v(1, 0) * v(3, 2)) - (v(3, 0) * v(1, 2));
	sub[11] = (v(1, 0) * v(3, 1)) - (v(3, 0) * v(1, 1));

	sub[12] = (v(1, 2) * v(2, 3)) - (v(2, 2) * v(1, 3));
	sub[13] = (v(1, 1) * v(2, 3)) - (v(2, 1) * v(1, 3));
	sub[14] = (v(1, 1) * v(2, 2)) - (v(2, 1) * v(1, 2));
	sub[15] = (v(1, 0) * v(2, 3)) - (v(2, 0) * v(1, 3));
	sub[16] = (v(1, 0) * v(2, 2)) - (v(2, 0) * v(1, 2));
	sub[17] = (v(1, 0) * v(2, 1)) - (v(2, 0) * v(1, 1));

	//More script generated cancer
	//Calculate cofactor matrix
	temp.v(0, 0) = v(1, 1) * (sub[0]) - v(1, 2) * (sub[1]) + v(1, 3) * (sub[2]);
	temp.v(0, 1) = -(v(1, 0) * (sub[0]) - v(1, 2) * (sub[3]) + v(1, 3) * (sub[4]));
	temp.v(0, 2) = v(1, 0) * (sub[1]) - v(1, 1) * (sub[3]) + v(1, 3) * (sub[5]);
	temp.v(0, 3) = -(v(1, 0) * (sub[2]) - v(1, 1) * (sub[4]) + v(1, 2) * (sub[5]));

	temp.v(1, 0) = -(v(0, 1) * (sub[0]) - v(0, 2) * (sub[1]) + v(0, 3) * (sub[2]));
	temp.v(1, 1) = v(0, 0) * (sub[0]) - v(0, 2) * (sub[3]) + v(0, 3) * (sub[4]);
	temp.v(1, 2) = -(v(0, 0) * (sub[1]) - v(0, 1) * (sub[3]) + v(0, 3) * (sub[5]));
	temp.v(1, 3) = v(0, 0) * (sub[2]) - v(0, 1) * (sub[4]) + v(0, 2) * (sub[5]);

	temp.v(2, 0) = v(0, 1) * (sub[6]) - v(0, 2) * (sub[7]) + v(0, 3) * (sub[8]);
	temp.v(2, 1) = -(v(0, 0) * (sub[6]) - v(0, 2) * (sub[9]) + v(0, 3) * (sub[10]));
	temp.v(2, 2) = v(0, 0) * (sub[7]) - v(0, 1) * (sub[9]) + v(0, 3) * (sub[11]);
	temp.v(2, 3) = -(v(0, 0) * (sub[8]) - v(0, 1) * (sub[10]) + v(0, 2) * (sub[11]));

	temp.v(3, 0) = -(v(0, 1) * (sub[12]) - v(0, 2) * (sub[13]) + v(0, 3) * (sub[14]));
	temp.v(3, 1) = v(0, 0) * (sub[12]) - v(0, 2) * (sub[15]) + v(0, 3) * (sub[16]);
	temp.v(3, 2) = -(v(0, 0) * (sub[13]) - v(0, 1) * (sub[15]) + v(0, 3) * (sub[17]));
	temp.v(3, 3) = v(0, 0) * (sub[14]) - v(0, 1) * (sub[16]) + v(0, 2) * (sub[17]);

	temp.transpose();

	this->operator=(temp / det);
}

void Matrix4x4f::transpose()
{
	Matrix4x4f temp = *this;

#define op(r, c) v(r, c) = temp.v(c, r)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()
}

void Matrix4x4f::translate(float x, float y, float z)
{
	Matrix4x4f temp = Matrix4x4f::identity;
	temp[0][3] = x;
	temp[1][3] = y;
	temp[2][3] = z;

	this->operator=(*this * temp);
}

void Matrix4x4f::scale(float sx, float sy, float sz)
{
	Matrix4x4f temp = Matrix4x4f::identity;
	temp[0][0] = sx;
	temp[1][1] = sy;
	temp[2][3] = sz;
	
	this->operator=(*this * temp);
}

void Matrix4x4f::rotateX(float angle)
{
	Matrix4x4f temp = Matrix4x4f::identity;

	const float _cos = cosf(angle);
	const float _sin = sinf(angle);

	temp[1][1] = _cos;
	temp[1][2] = _sin;
	temp[2][1] = -_sin;
	temp[2][2]= _cos;

	this->operator=(*this * temp);
}

void Matrix4x4f::rotateY(float angle)
{
	Matrix4x4f temp = Matrix4x4f::identity;

	const float _cos = cosf(angle);
	const float _sin = sinf(angle);

	temp[0][0] = _cos;
	temp[2][0] = _sin;
	temp[0][2] = -_sin;
	temp[2][2] = _cos;

	this->operator=(*this * temp);
}

void Matrix4x4f::rotateZ(float angle)
{
	Matrix4x4f temp = Matrix4x4f::identity;

	const float _cos = cosf(angle);
	const float _sin = sinf(angle);

	temp[0][0] = _cos;
	temp[1][0] = _sin;
	temp[0][1] = -_sin;
	temp[1][1] = _cos;

	this->operator=(*this * temp);
}

void Matrix4x4f::shear(float angle)
{
	Matrix4x4f temp = Matrix4x4f::identity;
	temp[0][1] = 1 / tanf(angle);
	temp[1][1] = 0;

	this->operator=(*this * temp);
}

Matrix4x4f Matrix4x4f::getPerspectiveMatrix(float fov, float aspect, float near, float far)
{
	const float range = near - far;
	const float t = tanf((fov * Deg2Rad) / 2);

	Matrix4x4f temp;
	temp[0][0] = 1 / (aspect * t);
	temp[1][1] = 1 / t;
	temp[2][2] = -(far + near) / range;
	temp[2][3] = (-2 * far * near) / range;
	temp[3][2] = -1;

	return temp;
}

Matrix4x4f::operator Matrix4x4d() const
{
	Matrix4x4d o;

#define op(r, c) o.v(r, c) = v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4f operator+(const Matrix4x4f& a, const Matrix4x4f& b)
{
	Matrix4x4f o = Matrix4x4f();

#define op(r, c) o.v(r, c) = a.v(r, c) + b.v(r, c)
	/*Operation*/ {
	op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4f operator-(const Matrix4x4f& a, const Matrix4x4f& b)
{
	Matrix4x4f o = Matrix4x4f();

#define op(r, c) o.v(r, c) = a.v(r, c) - b.v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4f operator*(const Matrix4x4f& a, const Matrix4x4f& b)
{
	Matrix4x4f o = Matrix4x4f();

#define op(r, c) o.v(r, c) = a.v(r, 0) * b.v(0, c) + a.v(r, 1) * b.v(1, c) + a.v(r, 2) * b.v(2, c) + a.v(r, 3) * b.v(3, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4f operator*(const Matrix4x4f& a, float b)
{
	Matrix4x4f o = Matrix4x4f();

#define op(r, c) o.v(r, c) = a.v(r, c) * b
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4f operator/(const Matrix4x4f& a, float b)
{
	Matrix4x4f o = Matrix4x4f();

#define op(r, c) o.v(r, c) = a.v(r, c) / b
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d::Matrix4x4d()
{
	std::fill(values, values + 16, 0);
}

Matrix4x4d::Matrix4x4d(const double values[16])
{
#define op(r, c) this->v(r, c) = v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()
}

Matrix4x4d::Matrix4x4d(double a00, double a01, double a02, double a03, double a10, double a11, double a12, double a13, double a20, double a21, double a22, double a23, double a30, double a31, double a32, double a33)
{
	v(0, 0) = a00; v(0, 1) = a01; v(0, 2) = a02; v(0, 3) = a03;
	v(1, 0) = a10; v(1, 1) = a11; v(1, 2) = a12; v(1, 3) = a13;
	v(2, 0) = a20; v(2, 1) = a21; v(2, 2) = a22; v(2, 3) = a23;
	v(3, 0) = a30; v(3, 1) = a31; v(3, 2) = a32; v(3, 3) = a33;
}

Matrix4x4d& Matrix4x4d::operator=(const Matrix4x4d& b)
{
#define op(r, c) v(r, c) = b.v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return *this;
}

Matrix4x4d& Matrix4x4d::operator=(const double values[16])
{
#define op(r, c) this->v(r, c) = v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return *this;
}

double* Matrix4x4d::operator[](int row)
{
	return values + row * 4;
}

const double* Matrix4x4d::operator[](int row) const
{
	return values + row * 4;
}

double Matrix4x4d::det()
{
	//Precaclulate stuff that gets used multiple times
	double sub[6];
	sub[0] = (v(2, 2) * v(3, 3)) - (v(3, 2) * v(2, 3));
	sub[1] = (v(2, 1) * v(3, 3)) - (v(3, 1) * v(2, 3));
	sub[2] = (v(2, 1) * v(3, 2)) - (v(3, 1) * v(2, 2));
	sub[3] = (v(2, 0) * v(3, 3)) - (v(3, 0) * v(2, 3));
	sub[4] = (v(2, 0) * v(3, 2)) - (v(3, 0) * v(2, 2));
	sub[5] = (v(2, 0) * v(3, 1)) - (v(3, 0) * v(2, 1));

	//I wrote a python script to spit this out. Sorry for the cancer I didn't want any recursion.
	return v(0, 0) * (v(1, 1) * (sub[0]) - v(1, 2) * (sub[1]) + v(1, 3) * (sub[2])) - v(0, 1) * (v(1, 0) * (sub[0]) - v(1, 2) * (sub[3]) + v(1, 3) * (sub[4])) + v(0, 2) * (v(1, 0) * (sub[1]) - v(1, 1) * (sub[3]) + v(1, 3) * (sub[5])) - v(0, 3) * (v(1, 0) * (sub[2]) - v(1, 1) * (sub[4]) + v(1, 2) * (sub[5]));
}

void Matrix4x4d::invert()
{
	double det = Matrix4x4d::det();

	if (det == 0)
		return;

	Matrix4x4d temp;

	//Precaclulate stuff that gets used multiple times
	double sub[18];
	sub[0] = (v(2, 2) * v(3, 3)) - (v(3, 2) * v(2, 3));
	sub[1] = (v(2, 1) * v(3, 3)) - (v(3, 1) * v(2, 3));
	sub[2] = (v(2, 1) * v(3, 2)) - (v(3, 1) * v(2, 2));
	sub[3] = (v(2, 0) * v(3, 3)) - (v(3, 0) * v(2, 3));
	sub[4] = (v(2, 0) * v(3, 2)) - (v(3, 0) * v(2, 2));
	sub[5] = (v(2, 0) * v(3, 1)) - (v(3, 0) * v(2, 1));

	sub[6] = (v(1, 2) * v(3, 3)) - (v(3, 2) * v(1, 3));
	sub[7] = (v(1, 1) * v(3, 3)) - (v(3, 1) * v(1, 3));
	sub[8] = (v(1, 1) * v(3, 2)) - (v(3, 1) * v(1, 2));
	sub[9] = (v(1, 0) * v(3, 3)) - (v(3, 0) * v(1, 3));
	sub[10] = (v(1, 0) * v(3, 2)) - (v(3, 0) * v(1, 2));
	sub[11] = (v(1, 0) * v(3, 1)) - (v(3, 0) * v(1, 1));

	sub[12] = (v(1, 2) * v(2, 3)) - (v(2, 2) * v(1, 3));
	sub[13] = (v(1, 1) * v(2, 3)) - (v(2, 1) * v(1, 3));
	sub[14] = (v(1, 1) * v(2, 2)) - (v(2, 1) * v(1, 2));
	sub[15] = (v(1, 0) * v(2, 3)) - (v(2, 0) * v(1, 3));
	sub[16] = (v(1, 0) * v(2, 2)) - (v(2, 0) * v(1, 2));
	sub[17] = (v(1, 0) * v(2, 1)) - (v(2, 0) * v(1, 1));

	//More script generated cancer
	//Calculate cofactor matrix
	temp.v(0, 0) = v(1, 1) * (sub[0]) - v(1, 2) * (sub[1]) + v(1, 3) * (sub[2]);
	temp.v(0, 1) = -(v(1, 0) * (sub[0]) - v(1, 2) * (sub[3]) + v(1, 3) * (sub[4]));
	temp.v(0, 2) = v(1, 0) * (sub[1]) - v(1, 1) * (sub[3]) + v(1, 3) * (sub[5]);
	temp.v(0, 3) = -(v(1, 0) * (sub[2]) - v(1, 1) * (sub[4]) + v(1, 2) * (sub[5]));

	temp.v(1, 0) = -(v(0, 1) * (sub[0]) - v(0, 2) * (sub[1]) + v(0, 3) * (sub[2]));
	temp.v(1, 1) = v(0, 0) * (sub[0]) - v(0, 2) * (sub[3]) + v(0, 3) * (sub[4]);
	temp.v(1, 2) = -(v(0, 0) * (sub[1]) - v(0, 1) * (sub[3]) + v(0, 3) * (sub[5]));
	temp.v(1, 3) = v(0, 0) * (sub[2]) - v(0, 1) * (sub[4]) + v(0, 2) * (sub[5]);

	temp.v(2, 0) = v(0, 1) * (sub[6]) - v(0, 2) * (sub[7]) + v(0, 3) * (sub[8]);
	temp.v(2, 1) = -(v(0, 0) * (sub[6]) - v(0, 2) * (sub[9]) + v(0, 3) * (sub[10]));
	temp.v(2, 2) = v(0, 0) * (sub[7]) - v(0, 1) * (sub[9]) + v(0, 3) * (sub[11]);
	temp.v(2, 3) = -(v(0, 0) * (sub[8]) - v(0, 1) * (sub[10]) + v(0, 2) * (sub[11]));

	temp.v(3, 0) = -(v(0, 1) * (sub[12]) - v(0, 2) * (sub[13]) + v(0, 3) * (sub[14]));
	temp.v(3, 1) = v(0, 0) * (sub[12]) - v(0, 2) * (sub[15]) + v(0, 3) * (sub[16]);
	temp.v(3, 2) = -(v(0, 0) * (sub[13]) - v(0, 1) * (sub[15]) + v(0, 3) * (sub[17]));
	temp.v(3, 3) = v(0, 0) * (sub[14]) - v(0, 1) * (sub[16]) + v(0, 2) * (sub[17]);

	temp.transpose();

	this->operator=(temp / det);
}

void Matrix4x4d::transpose()
{
	Matrix4x4d temp = *this;

#define op(r, c) v(r, c) = temp.v(c, r)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()
}

void Matrix4x4d::translate(double x, double y, double z)
{
	Matrix4x4d temp = Matrix4x4d::identity;
	temp[0][3] = x;
	temp[1][3] = y;
	temp[2][3] = z;

	this->operator=(*this * temp);
}

void Matrix4x4d::scale(double sx, double sy, double sz)
{
	Matrix4x4d temp = Matrix4x4d::identity;
	temp[0][0] = sx;
	temp[1][1] = sy;
	temp[2][3] = sz;

	this->operator=(*this * temp);
}

void Matrix4x4d::rotateX(double angle)
{
	Matrix4x4d temp = Matrix4x4d::identity;

	const double _cos = cos(angle);
	const double _sin = sin(angle);

	temp[1][1] = _cos;
	temp[1][2] = _sin;
	temp[2][1] = -_sin;
	temp[2][2] = _cos;

	this->operator=(*this * temp);
}

void Matrix4x4d::rotateY(double angle)
{
	Matrix4x4d temp = Matrix4x4d::identity;

	const double _cos = cos(angle);
	const double _sin = sin(angle);

	temp[0][0] = _cos;
	temp[2][0] = _sin;
	temp[0][2] = -_sin;
	temp[2][2] = _cos;

	this->operator=(*this * temp);
}

void Matrix4x4d::rotateZ(double angle)
{
	Matrix4x4d temp = Matrix4x4d::identity;

	const double _cos = cos(angle);
	const double _sin = sin(angle);

	temp[0][0] = _cos;
	temp[1][0] = _sin;
	temp[0][1] = -_sin;
	temp[1][1] = _cos;

	this->operator=(*this * temp);
}

void Matrix4x4d::shear(double angle)
{
	Matrix4x4d temp = Matrix4x4d::identity;
	temp[0][1] = 1 / tan(angle);
	temp[1][1] = 0;

	this->operator=(*this * temp);
}

Matrix4x4d Matrix4x4d::getPerspectiveMatrix(double fov, double aspect, double near, double far)
{
	const double range = far - near;
	const double t = tan((fov * Deg2Rad) / 2);

	Matrix4x4d temp;
	temp[0][0] = 1 / (aspect * t);
	temp[1][1] = 1 / t;
	temp[2][2] = -(far + near) / range;
	temp[2][3] = (-2 *far * near) / range;
	temp[3][2] = -1;

	return temp;
}

Matrix4x4d::operator Matrix4x4f() const
{
	Matrix4x4f o;

#define op(r, c) o.v(r, c) = (float) v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d operator+(const Matrix4x4d& a, const Matrix4x4d& b)
{
	Matrix4x4d o = Matrix4x4d();

#define op(r, c) o.v(r, c) = a.v(r, c) + b.v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d operator-(const Matrix4x4d& a, const Matrix4x4d& b)
{
	Matrix4x4d o = Matrix4x4d();

#define op(r, c) o.v(r, c) = a.v(r, c) - b.v(r, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d operator*(const Matrix4x4d& a, const Matrix4x4d& b)
{
	Matrix4x4d o = Matrix4x4d();

#define op(r, c) o.v(r, c) = a.v(r, 0) * b.v(0, c) + a.v(r, 1) * b.v(1, c) + a.v(r, 2) * b.v(2, c) + a.v(r, 3) * b.v(3, c)
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d operator*(const Matrix4x4d& a, double b)
{
	Matrix4x4d o = Matrix4x4d();

#define op(r, c) o.v(r, c) = a.v(r, c) * b
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}

Matrix4x4d operator/(const Matrix4x4d& a, double b)
{
	Matrix4x4d o = Matrix4x4d();

#define op(r, c) o.v(r, c) = a.v(r, c) / b
	/*Operation*/ {op(0, 0); op(0, 1); op(0, 2); op(0, 3);
	op(1, 0); op(1, 1); op(1, 2); op(1, 3);
	op(2, 0); op(2, 1); op(2, 2); op(2, 3);
	op(3, 0); op(3, 1); op(3, 2); op(3, 3); }
#undef op()

	return o;
}
