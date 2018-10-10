#include <iostream>
#include <string>
#include <fstream>
#include "tracer.h"
using namespace std;

int main() {
	Tracer trace;
	//Scene newscene;
	trace.init("test.obj");
	trace.render();
	trace.savepic("test.png");
	trace.ins("test.png");
	return 0;
}