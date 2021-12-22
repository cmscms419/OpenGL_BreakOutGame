#include "model.h"

bool collisionRect2Rect(Rect r1, Rect r2)
{
	return (r1.Left < r2.Right&& r1.Right > r2.Left &&
		r1.Top < r2.Bottom&& r1.Bottom > r2.Top);
}

bool collisionCircle2Circle(circle c1, circle c2)
{
	float squX = pow((c2.x - c1.x), 2.0);
	float squY = pow((c2.y - c1.y), 2.0);
	float addR = c1.radian + c2.radian;

	return (addR <= sqrt(squX + squY));
}