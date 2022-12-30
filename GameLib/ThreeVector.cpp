#include"ThreeVector.h"


ThreeDvector::ThreeDvector(float ex, float why, float zee)
{
	x = ex; y = why; z = zee;
}

ThreeDvector::~ThreeDvector() {}

float ThreeDvector::getMagnitude()const
{
	return sqrt(x * x + y * y + z * z);
}

ThreeDvector ThreeDvector::operator*(float num) const
{
	return ThreeDvector(num * x, num * y, num * z);
}

ThreeDvector  ThreeDvector::operator+(const ThreeDvector& vec)const
{
	return ThreeDvector(x + vec.x, y + vec.y, z + vec.z);
}

ThreeDvector  ThreeDvector::operator-(const ThreeDvector& vec)const
{
	return ThreeDvector(x - vec.x, y - vec.y, z - vec.z);
}

void  ThreeDvector::normalize3Dvector(void)
{
	float SQRT = sqrt(x * x + y * y + z * z);
	x /= SQRT; y /= SQRT; z /= SQRT;
}

float  ThreeDvector::dot3Dvector(const ThreeDvector& vec)const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

ThreeDvector  ThreeDvector::cross3Dvector(const ThreeDvector& vec)const
{
	return ThreeDvector(y * vec.z - z * vec.y,
		z * vec.x - x * vec.z,
		x * vec.y - y * vec.x);
}

ThreeDvector operator*(float num, const ThreeDvector& vec)
{
	return ThreeDvector(num * vec.x, num * vec.y, num * vec.z);
}

float ThreeDvector::angleBetween3dvectors(const ThreeDvector& vec) const
{
	return (acos(dot3Dvector(vec) / (getMagnitude() * vec.getMagnitude()))) * (180.0f / PI);
}