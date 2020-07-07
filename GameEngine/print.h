#pragma once

#include <iostream>
#include <iomanip>

#define println(a) std::cout << std::boolalpha << a << "\n"
#define print(a) std::cout << std::boolalpha << a

#if defined Vector_h && !defined Vector_p
#define Vector_p
std::ostream& operator << (std::ostream& out, const Vector3 vec);
std::ostream& operator << (std::ostream& out, const Vector2 vec);
std::ostream& operator << (std::ostream& out, const Point3 point);
#endif

#if defined Matrix_h && !defined Matrix_p
#define Matrix_p
std::ostream& operator << (std::ostream& out, const Matrix4x4f mat);
std::ostream& operator << (std::ostream& out, const Matrix4x4d mat);
#endif