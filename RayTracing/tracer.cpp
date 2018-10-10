#include "tracer.h"
#include <iostream>
#include "math.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Tracer::Tracer() {
	scene = new Scene();
	pic = Mat(PIXEL_H, PIXEL_W, CV_8UC3, Scalar(255,255, 255));
	

}

Color Tracer::check(Color c) {
	if (c.x > 1)
		c.x = 1;
	if (c.y > 1)
		c.y = 1;
	if (c.z > 1)
		c.z = 1;
	return c;
}

void Tracer::init(char* file) {
	scene->loadScene(file);
	cout << "读取完毕\n";
	Vector pos = Vector(20,-10,50);
	Color col = Color(0.6, 0.6, 0.6);
	PointLight k1;
	k1.set(pos, col);
	scene->addLight(k1);
	pos = Vector(-20, -10, 50);
	k1.set(pos, col);
	scene->addLight(k1);
}

Color Tracer::trace(Ray ray, int step) {
	float distance = INFINITY;
	Color col;
	col.x = col.y = col.z = 0.0;
	int faceCode=-1;
	Vector point;

	int p;
	if (p = scene->sphere.intersected(ray, distance)) {
		Vector d1 = ray.getDirection();
		d1.normalize();
		point = ray.getPoint(distance);
		Vector n = scene->sphere.getNorm(point);
		if(p == 1)
			n = -n;
		n.normalize();
		Vector ref;
		if (fabs(d1.dot(n) - 1) < 1e-3) {
			ref = n;
		}
		else{
			
			Vector dh = (d1.dot(n))*n;
			
			Vector dp = d1 - dh;
			dh.normalize();
			dp.normalize();
			//cout << "test " << dh.dot(dp)<< endl;
			float cos1 = n.dot(d1);
			float sin1 = sqrt(1 - cos1*cos1);
			float sin2;
			if (p == 1) {
			sin2 = sin1/1.2;
			}
			else if (p == -1)
			sin2 = sin1 * 1.2;
			else {
			cout << "ERROR";
			return Vector(1.0, 1.0, 1.0);
			}
			double theta = asin(sin2);
			//cout << "test2 " << cos(theta)*cos(theta) << " " << sin(theta)*sin(theta) << endl;
			dh = dh*cos(theta);
			dp = dp*sin(theta);
			//cout << "test3" << dh.dot(dh)+dp.dot(dp)<< endl;
			//cout << 2 * dp.dot(dh) << endl;
			ref = dh + dp;
			//cout << "test4 " << ref.dot(ref) << endl;
			//if (p == -1)
			//	cout << "inside" << " " << cos1 << endl;
			//cout << "theta1 " << acos(cos1) * 180 / 3.14159 << endl;
			//cout << "theta2 " << theta * 180 / 3.14159 << endl;
			//cout << ray.getOrigin().x << " " << ray.getOrigin().y << " " << ray.getOrigin().z << endl;
			//cout << "direc1 " << d1.x << " " << d1.y << " " << d1.z << endl;
			//cout<< "point " << " " << point.x << " " << point.y << " " << point.z << endl;
			//cout<< "direc2" << ref.x << " " << ref.y << " " << " " << ref.z << endl;
			//cout << "direc1 " << d1.x << " " << d1.y << " " << d1.z << endl;
			//cout << "point " << " " << point.x << " " << point.y << " " << point.z << endl;
			//cout << "norm"  << n.x << " " << n.y << " " << n.z << endl;
			//cout << "direc2" << ref.x << " " << ref.y << " " << " " << ref.z << endl;
			//system("pause");
		}
		
		return scene->sphere.col*trace(Ray(point + ref*SMALL, ref), step)*0.9;
	}/**/



	for (int k = 0;k < scene->triangleList.size();k++) {
		int p;
		if (p = scene->triangleList.at(k).intersected(ray, distance)) {
			faceCode = k;
		}
	}
	
	if (faceCode == -1) 
		return scene->amblight;
	//cout << "intersected\n";
	Triangle object = scene->triangleList.at(faceCode);
	point = ray.getPoint(distance);
	Vector norm = object.getNormal();
	norm.normalize();

	Vector dirView = viewPoint - point;
	dirView.normalize();

	for (int k = 0;k < scene->lightList.size();k++) {
		PointLight pot;
		pot.set(scene->lightList.at(k).getPosition(), scene->lightList.at(k).getColor());
		Vector l = pot.getPosition() - point;        //光源到交点
		l.normalize();
		Ray l_ray = Ray(point + l * SMALL, l);
		float shade = 1.0f;
		distance = INFINITY;
		for (int kh = 0;kh < scene->triangleList.size();kh++) {
			if (scene->triangleList.at(kh).intersected(l_ray, distance)) {
				shade = 0.2f;
				//cout << "but shadow\n";
				break;
			}
		}

		if (object.getDiffuse() > 0) {      //漫反射
			float cos = l.dot(norm);
			if (cos > 0) {
				float diffuse = cos*object.getDiffuse()*shade;
				//cout << col.x << " " << col.y << " " << col.z << endl;
				col = col + diffuse*(pot.getColor()*object.getColor());

				//cout << cos << " " << pot.getColor().x << " " << pot.getColor().y << " " << pot.getColor().z << " " << object.getColor().x << " " << object.getColor().y << " " << object.getColor().z << endl;
				//cout << col.x << " " << col.y << " " << col.z << endl;
				//system("pause");
			}
		}

		if (object.getSpec() > 0) {          //高光反射
			Vector h = 2 * norm.dot(l)*norm - l;
			float cos = h.dot(dirView);
			if (cos > 0) {
				float spec = powf(cos,20)*object.getSpec()*shade;
				col = col + spec*pot.getColor();
			}
		}

		if (object.getRefl() > 0 && step < DEPTH) {
			Vector refl = ray.getDirection() - 2 * norm.dot(ray.getDirection())*norm;
			col = col + trace(Ray(point + refl*SMALL, refl), ++step)*object.getRefl();
		}
	}
	//cout << col.x << " " << col.y << " " << col.z << endl;
	//system("pause");
	col = check(col);
	return col;

}

void Tracer::render() {
	viewPoint = Vector(0.0f, 0.0f, 30.0f);
	scene->loadScene("test.obj");
	scene->amblight = Color(135.0/255.0, 206.0/255.0, 235.0/255.0);

	float dx = (float)(VIEW_W / PIXEL_W);
	float dy = (float)(VIEW_H / PIXEL_H);
	float view_x = -VIEW_W / 2.0;
	float view_y = -VIEW_H / 2.0;
	int i, j;
	cout << "开始渲染" << endl;
#pragma omp parallel for private{i,j,view_x,view_y};
	for (i = 0;i < PIXEL_H;i++) {
		view_x = -VIEW_W / 2.0;;
		view_y = dy*(float)i - VIEW_H / 2.0;
		for (j = 0;j < PIXEL_W; j++) {
			Vector direc = Vector(view_x, view_y, 0) - viewPoint;
			direc.normalize();
			Ray ray(viewPoint, direc);
			//pic[j][i] = trace(ray, 1);
			Color col = trace(ray, 1);
			//cout << col.x << " " << col.y << " " << col.z << endl;
			//system("pause");
			//cout << i << " " << j << endl;
			pic.at<Vec3b>(i, j)[0] = (int)(col.z * 255);
			pic.at<Vec3b>(i, j)[1] = (int)(col.y * 255);
			pic.at<Vec3b>(i, j)[2] = (int)(col.x * 255);
			view_x = dx*(j + 1) - VIEW_W / 2.0;
		}

		if (i % 10 == 0&&i!=0) {
			cout << "Loading..." << i*100 / PIXEL_H << "%";
		}
	}
	namedWindow("test");
	imshow("test", pic);
	waitKey(0);
}

void Tracer::savepic(const char* file) {
	imwrite(file, pic);
}

void Tracer::ins(char* file) {
	Mat pic;
	pic = imread(file);
	//namedWindow("pic");
	//imshow("pic", pic);
	//waitKey(0);
	Mat pic2;
	GaussianBlur(pic, pic2, Size(3,3),0,0);
	medianBlur(pic2, pic2, 5);
	imwrite("test2.png", pic2);
}