#include "model.h"

static float radius = 0.1;

static GLfloat x = 0.0f, y = 0.0f; // 원의 중심 위치 값
static GLfloat dx = 0.01f, dy = 0.01f; // 원의 이동 크기(속도)
static GLfloat xDir = -1.0f, yDir = -0.8f; // 이동 방향

static GLfloat bar_x = -0.99f, bar_y = -1.0f; // bar의 초기 위치
static GLfloat Bheight = 0.05f, Blenght = 0.3f; // bar의 크기
static GLfloat Bspeed = 0.03f; // bar의 스피드
static GLfloat bDir = 1.0f; // bar의 방향


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
	if ((x < -0.9) || (x > 0.9))
	{
		xDir = -xDir;
	}

	if ((y < -0.9) || ( y > 0.9))
	{
		yDir = -yDir;
	}
}

void Bar::init()
{
	this->x = bar_x;
	this->y = bar_y;
	this->height = Bheight;
	this->lenght = Blenght;

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
		bar_x += bDir * Bspeed;
		break;
	case GLUT_KEY_LEFT:
		bar_x -= bDir * Bspeed;
		break;
	case GLUT_KEY_UP:
		dx += 0.001;
		dy += 0.001;
		break;
	case GLUT_KEY_DOWN:
		dx -= 0.001;
		dy -= 0.001;
		break;

	}
}

int checkpointInCircle(Circle c, GLfloat x, GLfloat y)
{
	GLfloat dx = c.x1 - x;
	GLfloat dy = c.y1 - y;
	GLfloat lenght = sqrt(dx * dx + dy * dy);

	if (lenght > c.rad)
		return 0;
	return 1;
}

int collisionSquareCircle(Bar bar, Circle circle)
{
	float Centerx = static_cast<float>(circle.x1);
	float Centery = static_cast<float>(circle.y1);
	float Raduis = static_cast<float>(radius);

	// 원의 중심이 사각형 근처에 왔다는 것을 판단한다.
	if (((bar.x + bar.lenght >= Centerx) && (bar.x <= Centerx))
		|| (((bar.y + bar.height) >= Centery) && (bar.y <= Centery)))
	{
		// bar의 위치를 계속 
		bar.collisionSquare = {
			bar.x - Raduis,
			bar.x + bar.lenght + Raduis,
			bar.y + bar.height + Raduis,
			bar.y - Raduis
		};

		// 위, 아래, 왼쪽, 오른쪽에 있는지 판단한다.
		if ((bar.collisionSquare.Left < Centerx && Centerx < bar.collisionSquare.Right) &&
			bar.collisionSquare.Bottom < Centery && Centery < bar.collisionSquare.Top)
		{
			return 1;
		}
		else // 좌상단, 좌하단, 우상단, 우하단에 있는 것을 판단한다.
		{
			// 좌상단
			if (checkpointInCircle(circle, bar.x, bar.y + bar.height))
				return 1;
			// 좌하단
			if (checkpointInCircle(circle, bar.x, bar.y))
				return 1;
			// 우상단
			if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y + bar.height))
				return 1;
			// 우하단
			if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y))
				return 1;
		}
	}

	return 0;
}

void Bound(Bar bar, Circle circle)
{
	switch (collisionSquareCircle(bar,circle))
	{
	case 1:
		yDir = -yDir;
		break;
	}
}
