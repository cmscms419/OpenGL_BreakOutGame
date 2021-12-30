#include "model.h"

#define AOC 0.003f		// 변화량
#define BARSPEED  0.03f	// bar의 스피드
#define Bheight 0.050	// bar의 크기
#define Blenght  0.30	// bar의 크기

#define SOL_F07 0.0055f // bar의 대각선을 구현하기 위해서, 값을 넣어준다.

static GLfloat radius = 0.03f;

static GLfloat x = 0.0f, y = -0.9f; // 원의 중심 위치 값
static GLfloat bar_x = -0.67f, bar_y = -1.0f; // bar의 초기 위치

static GLfloat dx = 0.005f, dy = 0.005f; // 이동 크기(속도)

static GLfloat xDir = -1.0f, yDir = -0.5f; // 원의 이동 방향
static GLfloat bDir = 1.0f; // bar의 방향


void Circle::init()
{
	this->x1 = x;
	this->y1 = y;
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
	if ((x - this->rad <= static_cast<GLfloat>(-0.9999)) || (x + this->rad >= static_cast<GLfloat>(0.9999)))
	{
		xDir = -xDir;
	}

	if ((y - this->rad <= static_cast<GLfloat>(-0.9999)) || (y + this->rad >= static_cast<GLfloat>(0.9999)))
	{
		yDir = -yDir;
	}
}

void Bar::init()
{
	this->x = bar_x * bDir;
	this->y = bar_y;
	this->height = Bheight;
	this->lenght = Blenght;

	// bar의 위치를 계속 
	this->collisionSquare = {
		this->x - radius,
		this->x + this->lenght + radius,
		this->y + this->height + radius,
		this->y - radius 
	};

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + this->lenght, y);
	glVertex2f(x, y + this->height);

	glVertex2f(x + this->lenght, y + this->height);
	glVertex2f(x + this->lenght, y);
	glVertex2f(x, y + this->height);
	glEnd();
}

void Bar::Barmove(int key)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		bar_x += static_cast<GLfloat>(bDir * BARSPEED);
		break;
	case GLUT_KEY_LEFT:
		bar_x -= static_cast<GLfloat>(bDir * BARSPEED);
		break;
	case GLUT_KEY_UP:
		dx += static_cast<GLfloat>(AOC);
		dy += static_cast<GLfloat>(AOC);
		break;
	case GLUT_KEY_DOWN:
		dx -= static_cast<GLfloat>(AOC);
		dy -= static_cast<GLfloat>(AOC);
		break;

	}
}

int checkpointInCircle(Circle c, GLfloat x, GLfloat y)
{
	float dx = c.x1 - x;
	float dy = c.y1 - y;
	float lenght = sqrt(dx * dx + dy * dy);

	if (lenght > radius + SOL_F07)
		return 0;
	return 1;
}

int collisionSquareCircle(Bar bar, Circle circle)
{
	// 위, 아래, 왼쪽, 오른쪽에 있는지 판단한다.
	if ((bar.collisionSquare.Left < circle.x1 && circle.x1 < bar.collisionSquare.Right) &&
		bar.collisionSquare.Bottom < circle.y1 && circle.y1 < bar.collisionSquare.Top)
	{
		// 왼쪽
		if (bar.x > circle.x1 && bar.y < circle.y1 && circle.y1 < bar.y + bar.height)
			return 1;
		// 오른쪽
		if (bar.x + bar.lenght < circle.x1 && bar.y < circle.y1 && circle.y1 < bar.y + bar.height)
			return 1;
		// 아래
		if (bar.y > circle.y1 && bar.x < circle.x1 && circle.x1 < bar.x + bar.lenght)
			return 2;
		// 위
		if (bar.y + bar.height < circle.y1 && bar.x < circle.x1 && circle.x1 < bar.x + bar.lenght)
			return 2;
	}
	// 좌상단, 좌하단, 우상단, 우하단에 있는 것을 판단한다.
	else 
	{
		// 좌상단
		if (checkpointInCircle(circle, bar.x, bar.y + bar.height))
			return 3;
		// 좌하단
		if (checkpointInCircle(circle, bar.x, bar.y))
			return 3;
		// 우상단
		if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y + bar.height))
			return 3;
		// 우하단
		if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y))
			return 3;
	}
	return 0;
}

void Bound(Bar bar, Circle circle)
{
	switch (collisionSquareCircle(bar, circle))
	{
	case 1:
		xDir = -xDir;
		break;
	case 2:
		yDir = -yDir;
		break;
	case 3:
		xDir = -xDir;
		yDir = -yDir;
		break;
	}
}
