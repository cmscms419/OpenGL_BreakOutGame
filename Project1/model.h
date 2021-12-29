#pragma once
#include <GL/glut.h>
#include <iostream>

typedef struct {
	float x, y;
	float radian;
}circle;

typedef struct {
	GLfloat Left, Right, Top, Bottom;
}Rect;

class Circle
{
public:
	GLfloat x1, y1, x2, y2;
	float angle;
	double rad;

	void init();
	void Circlemove();

	Circle() {};
	~Circle() {};
};

class Bar
{
public:
	GLfloat x, y;
	Rect collisionSquare;
	float height, lenght;
	
	void init();
	void Barmove(int key);

	Bar() {};
	~Bar() {};

};

int checkpointInCircle(Bar bar, GLfloat x, GLfloat y);
int collisionSquareCircle(Bar bar, Circle circle);
void Bound(Bar bar, Circle circle);