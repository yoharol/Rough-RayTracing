#include "Scene.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

void Scene::addLight(PointLight light) {
	lightList.push_back(light);
}

void Scene::getpoint(string a, int(&b)[3]) {
	//cout << a << endl;
	int temp = 0;
	int num = 0;
	int p = 0;
	while (num < a.length()) {
		if (a[num] == '/') {
			b[p] = temp;
			//cout << b[p] << endl;
			temp = 0;
			p++;
		}
		else {
			temp = temp * 10;
			temp += (int)(a[num] - '0');
		}
		num++;
	}
	b[p] = temp;
}

int Scene::getBlend(string name) {
	for (int i = 0;i < blendColor.size();i++) {
		if (blendColor[i].name == name)
			return i;
	}
}

void Scene::loadBlend(const char* file) {
	ifstream texture;
	texture.open(file);
	string a;
	while (!texture.eof()) {
		texture >> a;
		if (a == "newmtl") {
			Blend bcolor;
			texture >> a;
			bcolor.name = a;
			bcolor.refl = DEFAULTR;
			bcolor.spec = DEFAULTS;
			while (1) {
				texture >> a;
				if (a == "Kd") {
					float x, y, z;
					texture >> x >> y >> z;
					bcolor.Color.x = x;
					bcolor.Color.y = y;
					bcolor.Color.z = z;
				}
				if (a == "#refl") {
					float refl;
					texture >> refl;
					bcolor.refl = refl;
				}
				if (a == "Ks") {
					float r;
					texture >> r;
					bcolor.spec = r;
					break;
				}
			}
			blendColor.push_back(bcolor);
		}
	}
}

void Scene::loadScene(char* file) {
	sphere = Sphere();
	ifstream Model;
	Model.open(file);
	cout << "打开文件" << file << "成功\n";
	string a;
	int colorCode=0;
	while (!Model.eof()) {
		Model >> a;
		if (a == "mtllib") {
			string fname;
			Model >> fname;
			const char* name = fname.data();
			loadBlend(name);
			cout << "Load texture complete\n";
		}
		if (a == "usemtl") {
			Model >> a;
			colorCode = getBlend(a);
		}
		if (a == "v") {
			float x, y, z;
			Model >> x >> y >> z;
			Vector pot = Vector(x, y, z);
			pointList.push_back(pot);
		}

		if (a == "vn") {
			float x, y, z;
			Model >> x >> y >> z;
			Vector norm = Vector(x, y, z);
			normalList.push_back(norm);
		}

		if (a == "f") {
			//cout << "face " << triangleList.size() + 1 << endl;
			//cout << pointList.size() << " " << normalList.size() << " " << blendColor[colorCode].Color.x << endl;
			int b[3];
			Model >> a;
			getpoint(a, b);
			Vector t0 = pointList.at(b[0]-1);
			Vector norm = normalList.at(b[2]-1);
			Model >> a;
			getpoint(a, b);
			Vector t1 = pointList.at(b[0]-1);
			Model >> a;
			getpoint(a, b);
			Vector t2 = pointList.at(b[0]-1);
			Triangle tri = Triangle(t0, t1, t2, norm, blendColor[colorCode].Color);
			tri.setSpec(blendColor[colorCode].spec);
			tri.setRefl(blendColor[colorCode].refl);
			triangleList.push_back(tri);
		}

	}
	/*cout << "场景输入完成\n";

	for (int i = 0;i < triangleList.size();i++) {
		cout << "face " << i << endl;
		cout << triangleList[i].t0.x << " " << triangleList[i].t0.y << " " << triangleList[i].t0.z << endl;
		cout << triangleList[i].t1.x << " " << triangleList[i].t1.y << " " << triangleList[i].t1.z << endl;
		cout << triangleList[i].t2.x << " " << triangleList[i].t2.y << " " << triangleList[i].t2.z << endl;
		cout << triangleList[i].tnormal.x << " " << triangleList[i].tnormal.y << " " << triangleList[i].tnormal.z << endl;
		cout << triangleList[i].col.x << " " << triangleList[i].col.y << " " << triangleList[i].col.z << endl;
		cout << triangleList[i].refl << " " << triangleList[i].spec << endl;
	}
	system("pause");*/

}