#pragma once
#include <GL/glut.h>
#include <iostream>

typedef struct {
	float x, y;
	float radian;
}circle;

typedef struct {
	float Left, Right;
	float Top, Bottom;
}Rect;

class Circle
{
public:
	GLfloat x1, y1, x2, y2;
	float angle;
	double rad;

	void init();
	void Circlemove();
};

class Bar
{
public:
	GLfloat x, y;
	float hight, lenght;
	
	void init();
	void Barmove(int key);
	void collisionbarCircle();

};

bool checkbarInpoint(Bar bar, GLfloat x, GLfloat y);
void collisionbarCircle(Bar bar, Circle circle);