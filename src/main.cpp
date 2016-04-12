#include <SFML/Graphics.hpp>
#include <iostream>
#include "Physics\Sphere.h"
#include "Physics\Ray.h"
#include "Maths\Vector2.h"
#include "Maths\Quadratic.h"
#include "Graphics\Draw_Rays.h"

using namespace std;


int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(500, 500), "SFML works!", sf::Style::Default, settings);

	double r1 = 130;
	double r2 =130;
	Vector2 c1(150,250), c2(300,250);
	sf::Vertex line[] =
	{
		sf::Vertex(sf::Vector2f(0, 250),  sf::Color(255, 0, 0, 1)),
		sf::Vertex(sf::Vector2f(500, 250),  sf::Color(255, 0, 0, 1))
	};

	
	Sphere sphere(r1,r2,c1,c2,1.5);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear();
		sphere.DrawLense(&window);
		sphere.DiscreteSource(&window);
	//	sphere.DrawRays(ray, &window);
		window.draw(line, 2, sf::Lines);
	
		
		window.display();
	}
	
	return 0;
}