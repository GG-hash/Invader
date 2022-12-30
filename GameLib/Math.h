#pragma once
#include"GL/glut.h"
#include"glm/glm.hpp"
#include"TwoVector.h"
#include"ThreeVector.h"
using namespace glm;

struct Vector2int
{
	int x, y;

	Vector2int()
	{
		x = 0;
		y = 0;
	}

	Vector2int(int ex, int why) :x(ex), y(why)
	{

	}
};


class Math
{
};

