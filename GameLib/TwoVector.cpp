#include "TwoVector.h"


TwoDvector_comp TwoVector::TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec)
{
	TwoDvector_comp tmp = { 0,0 };

	tmp.x = vec.mag * cos(vec.dir * PI / 180.0f);
	tmp.y = vec.mag * sin(vec.dir * PI / 180.0f);

	return tmp;
}//TwoDvector_comp TwoVector::TwoDvector_comp_PolarToCompConversion(TwoDvector_polar vec)

TwoDvector_polar TwoVector::TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec)
{
	TwoDvector_polar tmp = { 0.0f,0.0f };

	tmp.mag = sqrt(vec.x * vec.x + vec.y * vec.y);

	// To prohibit divided by 0 
	if (tmp.mag == 0.0f)
		return tmp;
	//To ask degree
	tmp.dir = (180.0f / PI) * asin(vec.y / tmp.mag);

	// Recognize orthant

	// If vec.x is less than  0 , it must minus 180 degree .
	// This is 2 or 3 orthant
	if (vec.x < 0.0f)
		tmp.dir = 180.0f - tmp.dir;

	//This is 4 orthant.

	else if (vec.x > 0.0f && vec.y < 0.0f)
		tmp.dir += 360.0f;

	return tmp;
}//TwoDvector_polar TwoVector::TwoDvector_polar_CompToPolarConversion(TwoDvector_comp vec)