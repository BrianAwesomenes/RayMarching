#ifndef Vector_h
#define Vector_h

struct Point3;

struct Vector3 {
	float x;
	float y;
	float z;

	static Vector3 zero;
	static Vector3 one;

	Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

	static Vector3 cross(Vector3 a, Vector3 b);

	static float dot(Vector3 a, Vector3 b);

	Vector3 cross(Vector3 b);

	float dot(Vector3 b);

	float magnitude();

	Vector3 getUnit();

	void normalize();

	Vector3 normal();

	Vector3 operator +(Vector3 b);

	Vector3 operator -(Vector3 b);

	Vector3 operator *(float s);

	friend Vector3 operator* (float s, Vector3 v);

	Vector3 operator /(float s);

	explicit operator Point3() const;
};

struct Vector2 {
	float x;
	float y;

	static Vector2 zero;
	static Vector2 one;

	Vector2(float x = 0, float y = 0) : x(x), y(y) {}

	static float dot(Vector2 a, Vector2 b) {
		return a.x * b.x + a.y * b.y;
	}

	Vector2 operator +(Vector2 b) {
		return Vector2(x + b.x, y + b.y);
	}

	Vector2 operator -(Vector2 b) {
		return Vector2(x - b.x, y - b.y);
	}

	Vector2 operator *(float s) {
		return Vector2(x * s, y * s);
	}

	Vector2 operator /(float s) {
		return Vector2(x / s, y / s);
	}
};

struct Point3 {
	int x;
	int y;
	int z;

	static Point3 zero;
	static Point3 one;

	Point3(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

	Point3(const Point3& src) : x(src.x), y(src.y), z(src.z) {}

	Point3 operator +(Point3 b) {
		return Point3(x + b.x, y + b.y, z + b.z);
	}

	Point3 operator -(Point3 b) {
		return Point3(x - b.x, y - b.y, z - b.z);
	}

	Point3 operator *(int s) {
		return Point3(x * s, y * s, z * s);
	}

	Point3 operator /(int s) {
		return Point3(x / s, y / s, z / s);
	}

	operator Vector3() const { return Vector3(x, y, z); }
};

#endif