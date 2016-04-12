#pragma once 

#include "../Physics/World.h"
#include "../Physics/ControlManager.h"

#include <SFML/Graphics.hpp>
#include <iostream>

struct Scene: public sf::RenderWindow, public BirdController
{
  Scene(size_t width, size_t height): sf::RenderWindow(sf::VideoMode(width, height), "Flappy bird"), BirdController()
  {
  }

  bool IsForceApplied(size_t birdIndex, const World&) const
  {
  }

  void HandleEvents()
  {
  }

  void Draw(const World& world)
  {
  }
};
