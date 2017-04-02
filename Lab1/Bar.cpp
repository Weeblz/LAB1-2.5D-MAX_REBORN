#include "Bar.h"

std::vector<Figure>objects;
// default object sizing
double x = 1.0;
double y = 0.667;
double z = 0.667;

Bar::Bar(int width, int height, const std::string& title) {

	TwInit(TW_OPENGL_CORE, NULL);
	TwWindowSize(width, height);

	myBar = TwNewBar(title.c_str());

	TwAddVarRW(myBar, "xAxis", TW_TYPE_DOUBLE, &x, " keyincr=x keydecr=X min=0.1 max=10.0 step=0.01 ");
	TwAddVarRW(myBar, "yAxis", TW_TYPE_DOUBLE, &y, " keyincr=y keydecr=Y min=0.1 max=10.0 step=0.01 ");
	TwAddVarRW(myBar, "zAxis", TW_TYPE_DOUBLE, &z, " keyincr=z keydecr=Z min=0.1 max=10.0 step=0.01 ");
	
	TwAddButton(myBar, "NewEllipsoid", createEllipsoid, NULL, NULL);
	TwAddButton(myBar, "NewCuboid", createCuboid, NULL, NULL);
}

Bar::~Bar() {
	TwTerminate();
}

void TW_CALL createEllipsoid(void*) {
	objects.push_back(Figure(Ellipsoid, x, y, z));
}
void TW_CALL createCuboid(void*) {
	objects.push_back(Figure(Cuboid, x, y, z));
}