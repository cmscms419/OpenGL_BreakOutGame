#include "model.h"

#define AOC 0.003 // ��ȭ��
#define BARSPEED  0.03 // bar�� ���ǵ�

static GLfloat radius = 0.03f;

static GLfloat x = 0.0f, y = -0.95f; // ���� �߽� ��ġ ��
static GLfloat dx = 0.01f, dy = 0.01f; // ���� �̵� ũ��(�ӵ�)
static GLfloat xDir = -1.0f, yDir = -0.0f; // �̵� ����

static GLfloat bar_x = -0.7f, bar_y = -1.0f; // bar�� �ʱ� ��ġ
static GLfloat Bheight = 0.05f, Blenght = 0.3f; // bar�� ũ��
static GLfloat bDir = 1.0f; // bar�� ����


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


	// ���� ȭ�� ������ ����� �Ǹ� -1�� ���ؼ� ������ �ٲ۴�.
	// ���� �̵� ������ -1 ~ 1�̴�.
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

	if (lenght > radius)
		return 0;
	return 1;
}

int collisionSquareCircle(Bar bar, Circle circle)
{

	// ���� �߽��� �簢�� ��ó�� �Դٴ� ���� �Ǵ��Ѵ�.
	if (((bar.x + bar.lenght >= circle.x1) && (bar.x <= circle.x1))
		|| (((bar.y + bar.height) >= circle.y1) && (bar.y <= circle.y1)))
	{
		// bar�� ��ġ�� ��� 
		bar.collisionSquare = {
			bar.x - radius,
			bar.x + bar.lenght + radius,
			bar.y + bar.height + radius,
			bar.y - radius
		};

		// ��, �Ʒ�, ����, �����ʿ� �ִ��� �Ǵ��Ѵ�.
		if ((bar.collisionSquare.Left < circle.x1 && circle.x1 < bar.collisionSquare.Right) &&
			bar.collisionSquare.Bottom < circle.y1 && circle.y1 < bar.collisionSquare.Top)
		{
			// ����
			if (bar.x > circle.x1)
				return 1;
			// ������
			if (bar.x + bar.lenght < circle.x1)
				return 1;
			// �Ʒ�
			if (bar.y > circle.y1)
				return 2;
			// ��
			if (bar.y + bar.height < circle.y1)
				return 2;
		}
		else // �»��, ���ϴ�, ����, ���ϴܿ� �ִ� ���� �Ǵ��Ѵ�.
		{

			// �»��
			if (checkpointInCircle(circle, bar.x, bar.y + bar.height))
				return 3;
			// ���ϴ�
			if (checkpointInCircle(circle, bar.x, bar.y))
				return 3;
			// ����
			if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y + bar.height))
				return 3;
			// ���ϴ�
			if (checkpointInCircle(circle, bar.x + bar.lenght, bar.y))
				return 3;
		}
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
