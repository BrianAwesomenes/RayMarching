#ifndef Matrix_h
#define Matrix_h

class Matrix4x4d;

class Matrix4x4f {
	float values[16];
public:
	static const Matrix4x4f identity;

	Matrix4x4f();
	Matrix4x4f(const float values[16]);
	Matrix4x4f(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33);

	Matrix4x4f& operator =(const Matrix4x4f& b);
	Matrix4x4f& operator =(const float values[16]);
	float* operator [](int row);
	const float* operator [](int row) const;
	explicit operator float* () const { return (float*)values; }

	friend Matrix4x4f operator +(const Matrix4x4f& a, const Matrix4x4f& b);
	friend Matrix4x4f operator -(const Matrix4x4f& a, const Matrix4x4f& b);
	friend Matrix4x4f operator *(const Matrix4x4f& a, const Matrix4x4f& b);
	friend Matrix4x4f operator *(const Matrix4x4f& a, float b);
	friend Matrix4x4f operator /(const Matrix4x4f& a, float b);

	float det();
	void invert();
	void transpose();

	void translate(float x, float y, float z);
	void scale(float sx, float sy, float sz);
	void scale(float s) { scale(s, s, s); }
	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);
	void shear(float angle);

	static Matrix4x4f getPerspectiveMatrix(float fov, float aspect, float near, float far);

	friend class Matrix4x4d;
	operator Matrix4x4d() const;
};

Matrix4x4f operator +(const Matrix4x4f& a, const Matrix4x4f& b);
Matrix4x4f operator -(const Matrix4x4f& a, const Matrix4x4f& b);
Matrix4x4f operator *(const Matrix4x4f& a, const Matrix4x4f& b);
Matrix4x4f operator *(const Matrix4x4f& a, float b);
Matrix4x4f operator /(const Matrix4x4f& a, float b);

class Matrix4x4d {
	double values[16];
public:
	static const Matrix4x4d identity;

	Matrix4x4d();
	Matrix4x4d(const double values[16]);
	Matrix4x4d(
		double a00, double a01, double a02, double a03,
		double a10, double a11, double a12, double a13,
		double a20, double a21, double a22, double a23,
		double a30, double a31, double a32, double a33);

	Matrix4x4d& operator =(const Matrix4x4d& b);
	Matrix4x4d& operator =(const double values[16]);
	double* operator [](int row);
	const double* operator [](int row) const;
	explicit operator double* () const { return (double*) values; }

	friend Matrix4x4d operator +(const Matrix4x4d& a, const Matrix4x4d& b);
	friend Matrix4x4d operator -(const Matrix4x4d& a, const Matrix4x4d& b);
	friend Matrix4x4d operator *(const Matrix4x4d& a, const Matrix4x4d& b);
	friend Matrix4x4d operator *(const Matrix4x4d& a, double b);
	friend Matrix4x4d operator /(const Matrix4x4d& a, double b);

	double det();
	void invert();
	void transpose();

	void translate(double x, double y, double z);
	void scale(double sx, double sy, double sz);
	void scale(double s) { scale(s, s, s); }
	void rotateX(double angle);
	void rotateY(double angle);
	void rotateZ(double angle);
	void shear(double angle);

	static Matrix4x4d getPerspectiveMatrix(double fov, double aspect, double near, double far);

	friend class Matrix4x4f;
	explicit operator Matrix4x4f() const;
};

Matrix4x4d operator +(const Matrix4x4d& a, const Matrix4x4d& b);
Matrix4x4d operator -(const Matrix4x4d& a, const Matrix4x4d& b);
Matrix4x4d operator *(const Matrix4x4d& a, const Matrix4x4d& b);
Matrix4x4d operator *(const Matrix4x4d& a, double b);
Matrix4x4d operator /(const Matrix4x4d& a, double b);

#endif