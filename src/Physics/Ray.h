#pragma once
#include <SFML/Graphics.hpp>
#include "../Maths/Vector2.h"
#include "StraightLine.h"
#include "Sphere.h"
class Ray
{
  Vector2 startpoint;
  Vector2 direction;
  StraightLine equation;
  public:
	  Ray();
	  Ray(Vector2, Vector2);
	  StraightLine Equation();
	  Vector2 getBegin();
	  Vector2 getEnd();
	  void Draw(sf::RenderWindow *window);
	  void ResetParam(Vector2, Vector2);
	  void print();
};
