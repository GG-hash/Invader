#pragma once
#include<cmath>
#define PI 3.14159265f

class ThreeDvector
{
public:
	float x, y, z;
public:
	ThreeDvector(float ex = 0, float why = 0, float zee = 0);
	~ThreeDvector();
	float getMagnitude()const;
	ThreeDvector operator*(float num)const;
	friend ThreeDvector operator*(float num, const ThreeDvector& vec);
	ThreeDvector operator+(const ThreeDvector& vec)const;
	ThreeDvector operator-(const ThreeDvector& vec)const;
	void normalize3Dvector(void);
	float dot3Dvector(const ThreeDvector& vec)const;
	ThreeDvector cross3Dvector(const ThreeDvector& vec)const;
	float angleBetween3dvectors(const ThreeDvector& vec) const;
};