#include "Light.h"
#include <iostream>

Ray::Ray() {
	origin = Vector(0, 0, 0);
	direction = Vector(0, 0, 1);
}

Ray::Ray(Vector org, Vector dir) {
	this->origin = org;
	this->direction = dir;
}

Vector Ray::getPoint(float distance) {
	return origin + distance * direction;
}

Vector Ray::getDirection() {
	return direction;
}

Vector Ray::getOrigin() {
	return origin;
}

void Ray::setDirection(Vector org) {
	origin = org;
}

void Ray::setOrigin(Vector dir) {
	direction = dir;
}

PointLight::PointLight() {
	position = Vector(0, 0, 0);
	col = Vector(1, 1, 1);
}


void PointLight::set(Vector position, Color col) {
	this->position = position;
	this->col = col;
}

Color PointLight::getColor() {
	return col;
}

Vector PointLight::getPosition() {
	return position;
}