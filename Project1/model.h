
#define _CRT_SECURE_NO_WARNINGS 
#define STB_IMAGE_IMPLEMENTATION

#include <Windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <random>


#define RADIUS 0.03f

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
	GLfloat dx{}, dy{}, xDir{}, yDir{};
	GLfloat rad{};
	float angle{};

	void init();
	void Circlemove();

	Circle() {
		this->x1 = 0.0f;
		this->y1 = -0.9f;
		this->rad = RADIUS;
		this->dx = 0.005f;
		this->dy = 0.005f;
		this->xDir = -1.0f;
		this->yDir = -0.5f;
	};
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

	Bar() {
		this->x = -0.5f;
		this->y = -1.0f;
		this->height = 0.05f;
		this->lenght = 0.3f;
	};
	~Bar() {};
};

class Block
{
public:
	int stay{};
	GLfloat x{}, y{};
	GLfloat height = 0.1f, lenght = 0.2f;
	Rect collisionSquare{};

	void init(GLfloat x1, GLfloat y1);

	Block() {
		this->stay = 1;
	};

	~Block() {}
};



// 충돌 감지
int collisionSquareCircle(Bar bar, Circle circle);
int collisionSquareCircle2(Block bar, Circle circle);
int checkpointInCircle(Bar bar, GLfloat x, GLfloat y);
void Bound(Bar bar, Circle *circle);
void Bound2(Block *block, Circle *circle);
void Block_Bound(Block block[][MAX_X], int max_x, int max_y, Circle *ball);

// 블록 생성
void Block_init(Block block[][MAX_X], int max_x, int max_y);

// 블록삭제
void Del(Block *block);

//텍스처 매핑
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info);