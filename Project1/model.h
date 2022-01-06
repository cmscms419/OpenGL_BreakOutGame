
#define _CRT_SECURE_NO_WARNINGS 

#include <GL/glut.h>
#include <GL/GLAUX.H>
#include <FreeImage.h>
#include <iostream>
#include <random>

#define MAX_Y 3
#define MAX_X 10
#define AOC 0.003f		// 변화량
#define SOL_F07 0.01f // bar의 대각선을 구현하기 위해서, 값을 넣어준다.

//block
#define BLOCK_lenght 0.1f
#define BLOCK_height 0.05f
#define BLOCK_INI_X -0.6f
#define BLOCK_INI_Y 0.5f

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

class Block
{
public:
	int stay = 1;
	GLfloat x{}, y{};
	GLfloat height = 0.1f, lenght = 0.2f;
	Rect collisionSquare{};

	void init(GLfloat x1, GLfloat y1);
};

int checkpointInCircle(Bar bar, GLfloat x, GLfloat y);
int collisionSquareCircle(Bar bar, Circle circle);
int collisionSquareCircle2(Block bar, Circle circle);
void Bound(Bar bar, Circle circle);
void Bound2(Block *block, Circle circle);
void Block_init(Block block[][MAX_X], int max_x, int max_y);
void Block_Bound(Block block[][MAX_X], int max_x, int max_y, Circle ball);
void Del(Block *block);
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);