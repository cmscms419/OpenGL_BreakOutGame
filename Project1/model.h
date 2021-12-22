#pragma once
#include "model.h"
#include <stdio.h>
#include <math.h>


typedef struct {
	float x, y;
	float radian;
}circle;

typedef struct {
	float Left, Right;
	float Top, Bottom;
}Rect;

bool collisionRect2Rect(Rect r1, Rect r2);
bool collisionCircle2Circle(circle c1, circle c2);