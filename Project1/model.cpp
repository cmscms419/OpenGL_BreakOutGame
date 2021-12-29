#include "model.h"

static float radius = 0.1;

static GLfloat x = 0.0, y = 0.0; // 원의 중심 위치 값
static GLfloat dx = 0.01, dy = 0.01; // 원의 이동 크기(속도)
static GLfloat xDir = -1, yDir = -1.3; // 이동 방향

static GLfloat bar_x = -0.99, bar_y = -1; // bar의 초기 위치
static GLfloat Bhight = 0.05, Blenght = 0.3; // bar의 크기
static GLfloat Bspeed = 0.03; // bar의 스피드
static GLfloat bDir = 1.0; // bar의 방향


void Circle::init()
{
	this->x1 = x + dx;
	this->y1 = y + dy;
	this->rad = radius;

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + cos(angle) * rad;
		y2 = y1 + sin(angle) * rad;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Circle::Circlemove()
{
	x += xDir * dx;
	y += yDir * dy;

	// 원이 화면 범위를 벗어나게 되면 -1를 곱해서 방향을 바꾼다.
	// 원의 이동 범위는 -1 ~ 1이다.
	if ((xDir < 0 && x < -0.9) || (xDir > 0 && x > 0.9))
	{
		xDir = -xDir;
	}

	if ((yDir < 0 && y < -0.9) || (yDir > 0 && y > 0.9))
	{
		yDir = -yDir;
	}
}

void Bar::init()
{
	this->x = bar_x;
	this->y = bar_y;
	this->hight = Bhight;
	this->lenght = Blenght;

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + this->lenght, y);
	glVertex2f(x, y + this->hight);

	glVertex2f(x + this->lenght, y + this->hight);
	glVertex2f(x + this->lenght, y);
	glVertex2f(x, y + this->hight);
	glEnd();
}

void Bar::Barmove(int key)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		bar_x += bDir * Bspeed;
		break;
	case GLUT_KEY_LEFT:
		bar_x -= bDir * Bspeed;
		break;
	}
}

bool checkbarInpoint(Bar bar, GLfloat x, GLfloat y)
{
	if ((bar.x <= x || (bar.x + bar.lenght) >= x) &&
		(bar.y <= y || (bar.y + bar.hight) >= y))
	{
		return 1;
	}
	return 0;

}

void collisionbarCircle(Bar bar, Circle circle)
{
	
}