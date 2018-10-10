#include "vector.h"
#include "math.h"

Vector::Vector() {
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(const Vector& vec) {
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

float Vector::length() {
	return sqrt(x*x + y*y + z*z);
}

Vector Vector::cross(Vector b) {
	Vector ne = Vector(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	return ne;
}

float Vector::distance(Vector& b) {
	return (*this - b).length();
}

float Vector::dot(Vector b) {
	return x*b.x + y*b.y + z*b.z;
}

void Vector::normalize() {
	if (fabs(1 - (x*x + y*y + z*z)) < 1e-6)
		return;
	float l = sqrt(x*x + y*y + z*z);
	x /= l;
	y /= l;
	z /= l;
}

Vector Vector::operator - () const {
	return Vector(-x, -y, -z);
}

Vector operator + (const Vector& a, const Vector& b) {
	return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator - (const Vector &a, const Vector &b) {
	return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vector operator * (float f, const Vector& a) {
	return Vector(f*a.x, f*a.y, f*a.z);
}

Vector operator * (const Vector& a, float f) {
	return Vector(f*a.x, f*a.y, f*a.z);
}

Vector operator * (const Vector& a, const Vector& b) {
	return Vector(a.x*b.x, a.y*b.y, a.z*b.z);
}



bool operator == (const Vector &a, const Vector &b) {
	return (a.x == b.x&&a.y == b.y&&a.z == b.z);
}