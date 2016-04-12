#pragma once


#include "Shapes.h"
#include "../Maths/Vector2.h"
#include "Ray.h"
#include"Refraction.h"
class Ray;

struct Circle {
	double r;
	Vector2 center;
};
class Sphere //: public Shapes
{
	
	Circle c1, c2;
	std::vector<sf::Vertex> circle1;
	std::vector<sf::Vertex> circle2;
	double n;//показатель преломления
	void fillVertex();
	double* getParam(double, double, double);
	sf::Vertex way[4];
	public:
		Sphere(double, double, Vector2, Vector2,double);
		void DrawLense(sf::RenderWindow *window);
		Vector2 Intersect(StraightLine,Vector2,double, char);
		Circle getFirstCircle();
		Circle getSecondCircle();
		StraightLine Normal(Vector2,int);
		double sinAngle(StraightLine, StraightLine);
		void DrawRays(Ray, sf::RenderWindow *window);
		void DiscreteSource(sf::RenderWindow *window);
		void drawNormal(Vector2 p, StraightLine normal, sf::RenderWindow *window);
		StraightLine refr_line(StraightLine, double,Vector2,double);
		StraightLine external_reflection(StraightLine, double, Vector2, double);
};