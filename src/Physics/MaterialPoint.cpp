#include "MaterialPoint.h"

Vector2 MaterialPoint::GetImpulse() const
{
	return velocity * mass;
}