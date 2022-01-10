#include "model.h"

// Bar
static GLfloat bar_x = -0.5f, bar_y = -1.0f; // bar의 초기 위치
static GLfloat bDir = 1.0f; // bar의 방향
static GLfloat Blenght = 0.3f;	// bar의 크기
static GLfloat BARSPEED = 0.05f;	// bar의 스피드
static GLfloat Bheight = 0.05f;	// bar의 크기

// Block
static GLfloat blc_x = BLOCK_INI_X;
static GLfloat blc_y = BLOCK_INI_Y;

static GLfloat blc_l = 0.2f;
static GLfloat blc_h = 0.1f;

//Color
static GLfloat r;
static GLfloat g;
static GLfloat b;

void Circle::init()
{
	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2f)
	{
		this->x2 = this->x1 + cos(angle) * rad;
		this->y2 = this->y1 + sin(angle) * rad;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Circle::Circlemove()
{
	this->x1 += this->xDir * this->dx;
	this->y1 += this->yDir * this->dy;

	// 원이 화면 범위를 벗어나게 되면 -1를 곱해서 방향을 바꾼다.
	// 원의 이동 범위는 -1 ~ 1이다.
	if ((this->x1 - this->rad <=-0.999) || (this->x1 + this->rad >=0.999))
	{
		xDir = -xDir;
	}

	if ((this->y1 - this->rad <= -0.999) || (this->y1 + this->rad >= 0.999))
	{
		yDir = -yDir;
	}
}

void Bar::init()
{
	// bar의 위치를 계속 
	this->collisionSquare = {
		this->x - RADIUS,
		this->x + this->lenght + RADIUS,
		this->y + this->height + RADIUS,
		this->y - RADIUS
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
		this->x += bDir * BARSPEED;
		break;
	case GLUT_KEY_LEFT:
		this->x += -bDir * BARSPEED;
		break;
	}
}

void Block::init(GLfloat x1, GLfloat y1)
{
	if (this->stay)
	{
		this->x = x1;
		this->y = y1;
		this->height = BLOCK_height;
		this->lenght = BLOCK_lenght;

		this->collisionSquare =
		{
			this->x - RADIUS,
			this->x + this->lenght + RADIUS,
			this->y + this->height + RADIUS,
			this->y - RADIUS
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
}

int checkpointInCircle(Circle c, GLfloat x, GLfloat y)
{
	float dx = c.x1 - x;
	float dy = c.y1 - y;
	float lenght = sqrt(dx * dx + dy * dy);

	if (lenght > c.rad)
		return 0;
	return 1;
}

int collisionSquareCircle(Bar bar, Circle circle)
{
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

		// 좌상단, 좌하단, 우상단, 우하단에 있는 것을 판단한다.
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

int collisionSquareCircle2(Block bar, Circle circle)
{
	if (bar.stay)
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
	}
	return 0;
}

void Bound(Bar bar, Circle *circle)
{
	switch (collisionSquareCircle(bar, *circle))
	{
	case 1:
		circle->xDir = -circle->xDir;
		break;
	case 2:
		circle->yDir = -circle->yDir;
		break;
	case 3:
		circle->xDir = -circle->xDir;
		circle->yDir = -circle->yDir;
		break;
	}
}

void Bound2(Block* block, Circle *circle)
{
	switch (collisionSquareCircle2(*block, *circle))
	{
	case 1:
		circle->xDir = -circle->xDir;
		Del(block);
		break;
	case 2:
		circle->yDir = -circle->yDir;
		Del(block);
		break;
	case 3:
		circle->xDir = -circle->xDir;
		circle->yDir = -circle->yDir;
		Del(block);
		break;
	}
}

void Block_init(Block block[][MAX_X], int max_x, int max_y)
{
	for (int i = 0; i < max_y; i++)
	{
		for (int m = 0; m < max_x; m++)
		{
			block[i][m].init(blc_x, blc_y);
			blc_x += 0.12f;
		}
		blc_x = BLOCK_INI_X;
		blc_y = blc_y - 0.1f;
	}
}

void Block_Bound(Block block[][MAX_X], int max_x, int max_y, Circle *ball)
{
	for (int i = 0; i < MAX_Y; i++)
	{
		for (int m = 0; m < MAX_X; m++)
		{
			Bound2(&block[i][m], ball);
		}
		blc_x = BLOCK_INI_X;
		blc_y = blc_y - 0.1f;
	}

	blc_x = BLOCK_INI_X;
	blc_y = BLOCK_INI_Y;
}

void Del(Block* block)
{
	block->stay--;
}