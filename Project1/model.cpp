#include "model.h"

static float radius = 0.1;

static GLfloat x = 0.0f, y = 0.0f; // ���� �߽� ��ġ ��
static GLfloat dx = 0.01f, dy = 0.01f; // ���� �̵� ũ��(�ӵ�)
static GLfloat xDir = -1.0f, yDir = -0.8f; // �̵� ����

static GLfloat bar_x = -0.99f, bar_y = -1.0f; // bar�� �ʱ� ��ġ
static GLfloat Bheight = 0.05f, Blenght = 0.3f; // bar�� ũ��
static GLfloat Bspeed = 0.03f; // bar�� ���ǵ�
static GLfloat bDir = 1.0f; // bar�� ����


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

	// ���� �߽��� �簢�� ��ó�� �Դٴ� ���� �Ǵ��Ѵ�.
	if (((bar.x + bar.lenght >= Centerx) && (bar.x <= Centerx))
		|| (((bar.y + bar.height) >= Centery) && (bar.y <= Centery)))
	{
		// bar�� ��ġ�� ��� 
		bar.collisionSquare = {
			bar.x - Raduis,
			bar.x + bar.lenght + Raduis,
			bar.y + bar.height + Raduis,
			bar.y - Raduis
		};

		// ��, �Ʒ�, ����, �����ʿ� �ִ��� �Ǵ��Ѵ�.
		if ((bar.collisionSquare.Left < Centerx && Centerx < bar.collisionSquare.Right) &&
			bar.collisionSquare.Bottom < Centery && Centery < bar.collisionSquare.Top)
		{
			return 1;
		}
		else // �»��, ���ϴ�, ����, ���ϴܿ� �ִ� ���� �Ǵ��Ѵ�.
		{
			// �»��
			if (checkpointInCircle(circle, bar.x, bar.y + bar.height))
				return 1;
			// ���ϴ�
			if (checkpointInCircle(circle, bar.x, bar.y))
				return 1;
			// ����
			if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y + bar.height))
				return 1;
			// ���ϴ�
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
