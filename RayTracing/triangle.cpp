#include <iostream>
#include "triangle.h"

Triangle::Triangle() {
	t0 = Vector(0, 0, 0);
	t1 = Vector(-1, -1, 0);
	t2 = Vector(1, -1, 0);
	tnormal = Vector(0, 0, 1);
	col.x = col.y = col.z = 1.0f;
	spec = 0.4f;
	refl = 0.1f;
}


Triangle::Triangle(Vector a0, Vector a1, Vector a2, Vector nor) {
	t0 = a0;
	t1 = t1;
	t2 = a2;
	tnormal = nor;
	col.x = col.y = col.z = 1.0f;
	spec = 0.4f;
	refl = 0.05f;
}

void Triangle::setSpec(float spec) {
	this->spec = spec;
}

Triangle::Triangle(Vector a0, Vector a1, Vector a2, Vector nor, Color c) {
	t0 = a0;
	t1 = a1;
	t2 = a2;
	tnormal = nor;
	col.x = c.x;
	col.y = c.y;
	col.z = c.z;
	spec = 0.4f;
	refl = 0.05f;
}

Color Triangle::getColor() {
	return col;
}

float Triangle::getDiffuse() {
	return 1.0f - spec;
}

float Triangle::getRefl() {
	return refl;
}

float Triangle::getSpec() {
	return spec;
}

void Triangle::setRefl(float refl) {
	this->refl = refl;
}

Vector Triangle::getNormal() {
	return tnormal;
}

bool Triangle::InTriangle(const Vector& orig, const Vector& dir, float* t, float* u, float* v)
{
	Vector E1 = t1 - t0;
	Vector E2 = t2 - t0;
	Vector P(dir.y*E2.z - dir.z*E2.y, dir.z*E2.x - dir.x*E2.z, dir.x*E2.y - dir.y*E2.x);
	float det = E1.dot(P);
	Vector T;
	if (det >0)
	{
		T = orig -t0;
	}
	else
	{
		T = t0 - orig;
		det = -det;
	}
	if (det < 0.0001f)
		return false;

	*u = T.dot(P);
	if (*u < 0.0f || *u > det)
		return false;
	Vector Q = T.cross(E1);
	*v = dir.x*Q.x + dir.y*Q.y + dir.z*Q.z;;
	if (*v < 0.0f || *u + *v > det)
		return false;
	*t = E2.dot(Q);

	float fInvDet = 1.0f / det;
	*t *= fInvDet;
	*u *= fInvDet;
	*v *= fInvDet;

	return true;
}

INTERSECTION_TYPE Triangle::intersected(Ray ray, float& dist) {
	float cos = tnormal.dot(ray.getDirection());
	if (cos != 0)
	{
		float t = 0.0, u = 0.0, v = 0.0;
		if (InTriangle(ray.getOrigin(), ray.getDirection(), &t, &u, &v))
		{
			if (t>0 && t < dist)
			{
				dist = t;
				return INTERSECTED;
			}
		}
	}
	
	return MISS;
}

Sphere::Sphere() {
	t = 1.5;
	r = 1.8;
	cent = Vector(-1.5, -1.5, 6);
	col = Vector(0.85, 0.55, 0.55);
}

Vector Sphere::getCenter() {
	return cent;
}

Vector Sphere::getNorm(Vector point){
	Vector normal = point - cent;
	normal.normalize();
	return normal;
}

INTERSECTION_TYPE Sphere::intersected(Ray ray, float &dist) {
	float a = ray.getDirection().dot(ray.getDirection());
	Vector v = ray.getOrigin() - cent;
	float b = 2 * ray.getDirection().dot(v);
	float c = v.dot(v) - r * r;
	float det = b*b - 4 * a*c;
	INTERSECTION_TYPE inter = MISS;
	if (det>0)
	{
		det = sqrt(det);
		float t1 = (-b - det) / 2 * a;
		float t2 = (-b + det) / 2 * a;
		if (t2>0)
		{
			if (t1<0)
			{
				if (t2<dist)
				{
					dist = t2;
					inter = INSEC_IN;
				}
			}
			else
			{
				if (t1<dist)
				{
					dist = t1;
					inter = INTERSECTED;
				}
			}
		}
	}
	return inter;
}