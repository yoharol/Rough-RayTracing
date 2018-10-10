#pragma once
#ifndef _VECTOR_H
#define _VECTOR_H

#include "init.h"
#include "math.h"

class Vector {
public:
	Vector();
	Vector(float x, float y, float z);
	Vector(const Vector& vec);

	//void set(float x, float y, float z);
	//void set(Vector& vec);
	void normalize();
	float dot(Vector b);
	float length();
	float distance(Vector &b);
	Vector cross(Vector b);

	Vector operator- () const;

	friend Vector operator+ (const Vector& a, const Vector& b);
	friend Vector operator- (const Vector& a, const Vector& b);
	friend Vector operator* (const Vector& a, float f);
	friend Vector operator* (float f, const Vector& a);
	friend Vector operator* (const Vector& a, const Vector& b);
	friend bool operator== (const Vector& a, const Vector& b);
																
	float x, y, z;
};

typedef Vector Color;

#endif // !_VECTOR_H
