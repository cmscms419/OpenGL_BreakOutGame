#pragma once
#include <GL/glut.h>
#include <iostream>

typedef struct {
	GLfloat Left, Right, Top, Bottom;
}Rect;

class Circle
{
public:
	GLfloat x1{}, y1{}, x2{}, y2{};
	GLfloat rad{};
	float angle{};

	void init();
	void Circlemove();

	Circle() {};
	~Circle() {};
};

class Bar
{
public:
	GLfloat x{}, y{};
	GLfloat height{}, lenght{};
	Rect collisionSquare{};
	
	void init();
	void Barmove(int key);

	Bar() {};
	~Bar() {};

};

int checkpointInCircle(Bar bar, GLfloat x, GLfloat y);
int collisionSquareCircle(Bar bar, Circle circle);
void Bound(Bar bar, Circle circle);