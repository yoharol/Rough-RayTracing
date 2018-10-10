#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <stdlib.h>
#include <string>
#include <iostream>
#include "vector.h"
#include "Light.h"

using namespace std;


class Triangle {
public:
	Triangle();
	Triangle(Vector a0, Vector a1, Vector a2, Vector nor);
	Triangle(Vector a0, Vector a1, Vector a2, Vector nor, Color c);
	Color getColor();
	//float get_distance();
	float getSpec();
	float getRefl();
	float getDiffuse();
	void setRefl(float refl);
	void setSpec(float spec);
	Vector getNormal();
	bool InTriangle(const Vector& orig, const Vector& dir, float* t, float* u, float* v);
	INTERSECTION_TYPE intersected(Ray ray, float &dist);

//protected:
	float spec;
	float refl;
	Color col;
	Vector t0,t1,t2;
	Vector tnormal;
};

class Sphere {
public:
	Sphere();
	Vector getCenter();
	Vector getNorm(Vector point);
	INTERSECTION_TYPE intersected(Ray ray, float &dist);

	float t;
	float r;
	Vector cent;
	Color col;



};

typedef struct Blend
{
	Vector Color;
	string name;
	float spec;
	float refl;
}Blend;


#endif // !_TRIANGLE_H_
