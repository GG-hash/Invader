#pragma once

#define PI 3.14159265f
#include<cmath>
struct TwoDvector_comp
{//Member var
	float x, y;
};

struct TwoDvector_polar
{
	float mag, dir;
};
class TwoVector
{
public:

	TwoDvector_comp TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec);
	TwoDvector_polar TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec);
};//class TwoVector