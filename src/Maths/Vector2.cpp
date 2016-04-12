#include "Vector2.h"

Vector2::Vector2(double x = 0, double y = 0)
{
	this->x = x;
	this->y = y;
}

double Vector2::Len() const
{
	return sqrt(this->x * this->x + this->y * this->y);
}