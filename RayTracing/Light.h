#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <stdlib.h>
#include "init.h"
#include "vector.h"


class PointLight {
public:
	PointLight();
	Vector getPosition();
	Color getColor();
	void set(Vector position, Color col);
private:
	Vector position;
	Color col;
};

class Ray {
public:
	Ray();
	Ray(Vector org, Vector dir);
	Vector getOrigin();
	Vector getDirection();
	Vector getPoint(float distance);
	void setOrigin(Vector org);
	void setDirection(Vector dir);
	
private:
	Vector origin;
	Vector direction;

};

#endif // !_LIGHT_H_
