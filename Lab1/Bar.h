#pragma once
#include <string>
#include <vector>
#include <AntTweakBar.h>
#include "Figure.h"

extern std::vector<Figure>objects;

class Bar {
public:
	Bar(int width, int heigth, const std::string& title);
	virtual ~Bar();

private:
	TwBar *myBar;
};

void TW_CALL createEllipsoid(void*);
void TW_CALL createCuboid(void*);