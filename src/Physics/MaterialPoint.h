#include "../Maths/Vector2.h"

class MaterialPoint
{
public:
	MaterialPoint() 
	{
		position = Vector2(0, 0);
		velocity = Vector2(0, 0);
	}

	//virtual ~MaterialPoint();
	virtual void UpdatePosition(float dt) {}

	Vector2 position;
	Vector2 velocity;
}; 
