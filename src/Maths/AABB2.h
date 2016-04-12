#pragma once

#include "Vector2.h"

class AABB2
{
private:
  bool empty;

public:
  AABB2()
  {
    empty = true;
  }
  AABB2(const Vector2& boxPoint1, const Vector2& boxPoint2)
  {
    empty = true;
    Set(boxPoint1, boxPoint2);
  }

  bool Intersects(const AABB2& aabb) const
  {
    if (empty || aabb.empty) return false;
    if (boxPoint1.x > aabb.boxPoint2.x || aabb.boxPoint1.x > boxPoint2.x) return false;
    if (boxPoint1.y > aabb.boxPoint2.y || aabb.boxPoint1.y > boxPoint2.y) return false;
    return true;
  }

  bool Includes(const Vector2& point) const
  {
    if (empty) return false;
    if ((point.x < boxPoint1.x) || (point.x > boxPoint2.x) ||
      (point.y < boxPoint1.y) || (point.y > boxPoint2.y))
    {
      return false;
    }
    return true;
  }

  bool Includes(const AABB2& aabb) const
  {
    return Includes(aabb.boxPoint1) && Includes(aabb.boxPoint2);
  }

  void Set(const Vector2& boxPoint1, const Vector2& boxPoint2)
  {
    empty = false;
    this->boxPoint1 = boxPoint1;
    this->boxPoint2 = boxPoint2;
  }

  void Expand(const Vector2& additionalPoint)
  {
    if (empty)
    {
      empty = false;
      boxPoint1 = additionalPoint;
      boxPoint2 = additionalPoint;
    }else
    {
      boxPoint1.x = std::min(boxPoint1.x, additionalPoint.x);
      boxPoint1.y = std::min(boxPoint1.y, additionalPoint.y);
      boxPoint2.x = std::max(boxPoint2.x, additionalPoint.x);
      boxPoint2.y = std::max(boxPoint2.y, additionalPoint.y);
    }
  }
  void Expand(const AABB2& internalAABB)
  {
    Expand(internalAABB.boxPoint1);
    Expand(internalAABB.boxPoint2);
  }

  void Expand(const float mult)
  {
    Vector2 size = boxPoint2 - boxPoint1;
    boxPoint1 = boxPoint1 - size * (mult - 1.0f) * 0.5f;
    boxPoint2 = boxPoint2+ size * (mult - 1.0f) * 0.5f;
  }

  void Move(const Vector2& offset)
  {
    boxPoint1 = boxPoint1 + offset;
    boxPoint2 = boxPoint2 + offset;
  }

  void Move(float offsetX, float offsetY)
  {
    boxPoint1.x += offsetX;
    boxPoint2.x += offsetX;
    boxPoint1.y += offsetY;
    boxPoint2.y += offsetY;
  }

  Vector2 GetSize() const
  {
    return boxPoint2 - boxPoint1;
  }

  Vector2 boxPoint1, boxPoint2;
};
