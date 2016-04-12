#pragma once
#include <math.h>

class Vector2
{
public:
	Vector2()
	{
		x = 0;
		y = 0;
	}
	Vector2(double, double);
	Vector2 operator=(const Vector2& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}
	double operator *(const Vector2& a)
	{
		double b = x*a.x + y*a.y;
		return b;
	}
	Vector2 operator+(const Vector2& a) const
	{
		return Vector2(x + a.x, y + a.y);
	}
	double operator^(const Vector2& a) 
	{
		return x*a.y - y*a.x;
	}
	Vector2 operator-(const Vector2& a) const
	{
		return Vector2(x - a.x, y - a.y);
	}

	Vector2 operator*(float a) const
	{
		return Vector2(x * a, y * a);
	}

	Vector2 operator/(float a) const
	{
		return Vector2(x/a, y / a);
	}
	double Len() const;
	double x, y;
};
