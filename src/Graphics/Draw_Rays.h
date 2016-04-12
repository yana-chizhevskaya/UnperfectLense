#pragma once
#include "../Physics/Ray.h"
#include "../Physics/Sphere.h"
#include <SFML\Graphics.hpp>
void Draw_Rays(Ray ray, sf::RenderWindow *window) {
	ray.Draw(window);
}