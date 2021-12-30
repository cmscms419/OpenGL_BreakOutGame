#include "model.h"

#define AOC 0.003f		// ��ȭ��
#define BARSPEED  0.03f	// bar�� ���ǵ�
#define Bheight 0.050	// bar�� ũ��
#define Blenght  0.30	// bar�� ũ��

#define SOL_F07 0.0055f // bar�� �밢���� �����ϱ� ���ؼ�, ���� �־��ش�.

static GLfloat radius = 0.03f;

static GLfloat x = 0.0f, y = -0.9f; // ���� �߽� ��ġ ��
static GLfloat bar_x = -0.67f, bar_y = -1.0f; // bar�� �ʱ� ��ġ

static GLfloat dx = 0.005f, dy = 0.005f; // �̵� ũ��(�ӵ�)

static GLfloat xDir = -1.0f, yDir = -0.5f; // ���� �̵� ����
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
	this->x = bar_x * bDir;
	this->y = bar_y;
	this->height = Bheight;
	this->lenght = Blenght;

	// bar�� ��ġ�� ��� 
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
	// ��, �Ʒ�, ����, �����ʿ� �ִ��� �Ǵ��Ѵ�.
	if ((bar.collisionSquare.Left < circle.x1 && circle.x1 < bar.collisionSquare.Right) &&
		bar.collisionSquare.Bottom < circle.y1 && circle.y1 < bar.collisionSquare.Top)
	{
		// ����
		if (bar.x > circle.x1 && bar.y < circle.y1 && circle.y1 < bar.y + bar.height)
			return 1;
		// ������
		if (bar.x + bar.lenght < circle.x1 && bar.y < circle.y1 && circle.y1 < bar.y + bar.height)
			return 1;
		// �Ʒ�
		if (bar.y > circle.y1 && bar.x < circle.x1 && circle.x1 < bar.x + bar.lenght)
			return 2;
		// ��
		if (bar.y + bar.height < circle.y1 && bar.x < circle.x1 && circle.x1 < bar.x + bar.lenght)
			return 2;
	}
	// �»��, ���ϴ�, ����, ���ϴܿ� �ִ� ���� �Ǵ��Ѵ�.
	else 
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
