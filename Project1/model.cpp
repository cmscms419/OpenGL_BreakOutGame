#include "model.h"

static float radius = 0.1;

static GLfloat x = 0.0, y = 0.0; // ���� �߽� ��ġ ��
static GLfloat dx = 0.01, dy = 0.01; // ���� �̵� ũ��(�ӵ�)
static GLfloat xDir = -1, yDir = -1.3; // �̵� ����

static GLfloat bar_x = -0.99, bar_y = -1; // bar�� �ʱ� ��ġ
static GLfloat Bhight = 0.05, Blenght = 0.3; // bar�� ũ��
static GLfloat Bspeed = 0.03; // bar�� ���ǵ�
static GLfloat bDir = 1.0; // bar�� ����


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

	// ���� ȭ�� ������ ����� �Ǹ� -1�� ���ؼ� ������ �ٲ۴�.
	// ���� �̵� ������ -1 ~ 1�̴�.
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