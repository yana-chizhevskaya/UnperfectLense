#pragma once

#include "World.h"
#include <vector>

struct BirdController
{
  virtual bool IsForceApplied(size_t birdIndex, const World& world) const = 0;
};

struct ControlManager
{
  std::vector<BirdController*> controllers;

  void ApplyForces(World& world)
  {
    for (size_t i = 0; i < world.birds.size(); ++i)
    {
      bool isForceApplied = controllers[i]->IsForceApplied(i, world);
      if (isForceApplied)
        world.ApplyForce(i);
      else
        world.ReleaseForce(i);
    }
  }
};
