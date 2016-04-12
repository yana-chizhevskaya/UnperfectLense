#include"Refraction.h"
#include<math.h>
void refraction(Sphere lense, Ray ray, double n, sf::RenderWindow *window) {

	/*double len = sqrt((ray.getBegin().x - ray.getEnd().x)*(ray.getBegin().x -
		ray.getEnd().x) + (ray.getBegin().y - ray.getEnd().y) *(ray.getBegin().y - ray.getEnd().y));*/
	
	//cout << "I AM HERE" << endl;
	cout << "RAY 1" << endl;
	ray.print();
	double len = ray.getEnd().x - ray.getBegin().x;//длина луча до преломления
	double r_len = n / ((1 / len) - (1 - n) / lense.getSecondCircle().r);//длина луча после преломления
	Vector2 new_end(r_len+len, 250);
	Ray refr_ray(ray.getEnd(), new_end);
	cout << "RAY 0" << endl;
	refr_ray.print();
	Vector2 second_cross = lense.Intersect(refr_ray.Equation(), lense.getFirstCircle().center, lense.getFirstCircle().r, '+');
	refr_ray.ResetParam(ray.getEnd(), second_cross);
	cout << "RAY 2" << endl;
	refr_ray.print();
	double res = 1 / ((n / r_len) - (n - 1) / lense.getFirstCircle().r);
	Ray res_ray(refr_ray.getEnd(), Vector2(res, 250));
	cout << "RAY 3" << endl;
	res_ray.print();
	sf::Vertex way[] =
	{
		sf::Vertex(sf::Vector2f(ray.getBegin().x, 250)),
		sf::Vertex(sf::Vector2f(ray.getEnd().x, ray.getEnd().y)),
		sf::Vertex(sf::Vector2f(refr_ray.getEnd().x,refr_ray.getEnd().y)),
		sf::Vertex(sf::Vector2f(res_ray.getEnd().x, res_ray.getEnd().y)),

	};
	window->draw(way, 2, sf::Lines);
}

