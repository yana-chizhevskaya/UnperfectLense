#include "Ray.h"

Ray::Ray()
{
	startpoint.x = 0;
	startpoint.y = 0;
	direction.x = 0;
	direction.y = 0;
}

Ray::Ray(Vector2 a, Vector2 b) {
	this->startpoint = a;
	this->direction = b;
}

void Ray::Draw(sf::RenderWindow *window) {
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(startpoint.x, startpoint.y), sf:: Color(255, 0, 0, 1)),
		sf::Vertex(sf::Vector2f(direction.x, direction.y),  sf::Color(255, 0, 0, 1))
	};
	window->draw(line, 2, sf::Lines);
	
}
void Ray::ResetParam(Vector2 a, Vector2 b)
{
	this->startpoint = a;
	this->direction = b;
}
void Ray::print()
{
	cout << startpoint.x << "  " << startpoint.y << endl;
	cout << direction.x << "  " << direction.y << endl;

}
StraightLine Ray::Equation() {
	equation.a  = ( direction.y - startpoint.y) / (direction.x - startpoint.x);
	equation.b = startpoint.y - (equation.a *startpoint.x);
	return equation;
}

Vector2 Ray::getBegin() {
	return startpoint;
}

Vector2 Ray::getEnd()
{
	return direction;
}
