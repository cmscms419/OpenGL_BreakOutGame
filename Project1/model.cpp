#include "model.h"


// Ball
static GLfloat radius = 0.03f;

static GLfloat x_c = 0.0f, y_c = -0.9f; // 원의 중심 위치 값
static GLfloat dx = 0.005f, dy = 0.005f; // 이동 크기(속도)
static GLfloat xDir = -1.0f, yDir = -0.5f; // 원의 이동 방향

// Bar
static GLfloat bar_x = -0.5f, bar_y = -1.0f; // bar의 초기 위치
static GLfloat bDir = 1.0f; // bar의 방향
static GLfloat Blenght = 0.3f;	// bar의 크기
static GLfloat BARSPEED = 0.025f;	// bar의 스피드
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

//Texture
GLfloat position[] = {
	0.0f, 0.0f, // 왼쪽 아래
	0.0f, 1.0f, // 왼쪽 위
	1.0f, 1.0f, // 오른쪽 위
	1.0f, 0.0f	// 오른쪽 아래
};

GLfloat color[] = {
	1.0f, 0.0f, 0.0f, //vertex 1 : RED (1,0,0)
	0.0f, 1.0f, 0.0f, //vertex 2 : GREEN (0,1,0) 
	0.0f, 0.0f, 1.0f  //vertex 3 : BLUE (0,0,1)
};

GLfloat textureCoordinate[] = {
	0.0f, 0.0f, // 왼쪽 아래
	0.0f, 1.0f, // 왼쪽 위
	1.0f, 1.0f, // 오른쪽 위
	1.0f, 0.0f	// 오른쪽 아래      
};


GLuint trianglePositionVertexBufferObjectID, triangleColorVertexBufferObjectID;
GLuint triangleTextureCoordinateBufferObjectID;

void Circle::init()
{
	this->x1 = x_c;
	this->y1 = y_c;
	this->rad = radius;

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2f)
	{
		x2 = x1 + cos(angle) * rad;
		y2 = y1 + sin(angle) * rad;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void Circle::Circlemove()
{
	x_c += xDir * dx;
	y_c += yDir * dy;

	// 원이 화면 범위를 벗어나게 되면 -1를 곱해서 방향을 바꾼다.
	// 원의 이동 범위는 -1 ~ 1이다.
	if ((x_c - this->rad <= static_cast<GLfloat>(-0.999)) || (x_c + this->rad >= static_cast<GLfloat>(0.999)))
	{
		xDir = -xDir;
	}

	if ((y_c - this->rad <= static_cast<GLfloat>(-0.999)) || (y_c + this->rad >= static_cast<GLfloat>(0.999)))
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
		bar_x += static_cast<GLfloat>(-bDir * BARSPEED);
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
			this->x - radius,
			this->x + this->lenght + radius,
			this->y + this->height + radius,
			this->y - radius
		};
		for (int i = 0; i < 3; i++)
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<int> dis(0, 1);
		}

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

	if (lenght > radius)
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

void Bound2(Block* block, Circle circle)
{
	switch (collisionSquareCircle2(*block, circle))
	{
	case 1:
		xDir = -xDir;
		Del(block);
		break;
	case 2:
		yDir = -yDir;
		Del(block);
		break;
	case 3:
		xDir = -xDir;
		yDir = -yDir;
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

void Block_Bound(Block block[][MAX_X], int max_x, int max_y, Circle ball)
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
	block->stay = 0;
}


// [출처] [OpenGL] 예제12번을 응용한 텍스쳐매핑 예제16 | 작성자 송주씨
/*
GLubyte* LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE* fp;
	GLubyte* bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
			(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char*)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}
*/