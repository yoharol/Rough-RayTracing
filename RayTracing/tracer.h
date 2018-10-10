#ifndef _TRACER_H_
#define _TRACER_

#include "Scene.h"
#include "init.h"
#include <opencv2/opencv.hpp>

class Tracer {
public:
	Tracer();
	Vector trace(Ray ray,int step);
	Color check(Color c);
	void render();
	void savepic(const char* file);
	void init(char* file);
	void ins(char* file);

	Scene *scene;
	Vector viewPoint;
	Vector picPoint;
	cv::Mat pic;
	//Color pic[PIXEL_W][PIXEL_H];
};

#endif
