#ifndef _SCENE_H_
#define _SCENE_H_

#include "triangle.h"
#include <vector>

using namespace std;

class Scene {
public:
	void loadScene(char* file);
	void loadBlend(const char*file);
	void getpoint(string a, int(&b)[3]);
	int Scene::getBlend(string name);
	void addLight(PointLight light);

	vector<Vector> pointList;
	vector<Vector> normalList;
	vector<Triangle> triangleList;
	vector<Blend> blendColor;
	vector<PointLight> lightList;

	Color amblight;

	Sphere sphere;
};

#endif // !_SCENE_H_
