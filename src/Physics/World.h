#pragma once

#include "Bird.h"
#include "Gate.h"
#include "../Maths/AABB2.h"

#include <vector>

struct World
{
  static const Vector2 Gravity;
  static const Vector2 ExternalForce;
  static const size_t GatesCount = 3;
  static const float HorizontalVelocity;

  std::vector<Bird> birds;
  std::vector<Gate> gates;
  AABB2 frame;

  World(const AABB2& frame)
  {
    this->frame = frame;
  }

  void ApplyForce(size_t birdIndex)
  {
    birds[birdIndex].acceleration = ExternalForce / birds[birdIndex].m + Gravity;
  }

  void ReleaseForce(size_t birdIndex)
  {
    birds[birdIndex].acceleration = Gravity;
  }

  void Initialize(size_t birdsCount)
  {
  }

  void Update(float dt)
  {
  }

private:
  bool IsCollided(const Bird& bird, const Gate& gate)
  {
  }
};

const Vector2 World::Gravity = Vector2(0.0f, 50.0f);
const float World::HorizontalVelocity = 50;
const Vector2 World::ExternalForce(0, -150);
