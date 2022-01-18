#include "model.h"
#include <stb_image.h>

Circle ball;
Bar bar;
Block block[MAX_Y][MAX_X];

GLubyte* pbytes; // 데이터를 가리킬 포인터
BITMAPINFO* info; // 비트맵 헤더 저장할 변수
GLuint texture[3]; // 텍스처의 수

int count = 0;

void Display()
{
	// 화면과 깊이 버퍼를 지움
	//glClearColor(1.0, 0.24, 0.5, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 전에 있는 원의 흔적을 지운다.

	bar.init(texture[2]);
	ball.init(texture[0]);
	Block_init(block, MAX_X, MAX_Y, texture[1]);
	glFlush();

	Bound(bar, &ball);
	Block_Bound(block, MAX_X, MAX_Y, &ball);
	ball.Circlemove();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{

}

void Special(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_UP:
		ball.dx += static_cast<GLfloat>(AOC);
		ball.dy += static_cast<GLfloat>(AOC);
		break;
	case GLUT_KEY_DOWN:
		ball.dx -= static_cast<GLfloat>(AOC);
		ball.dy -= static_cast<GLfloat>(AOC);
		break;
	default:
		bar.Barmove(key);
		break;
	}
}

void reshape_func(int width, int height)
{
	glViewport(0, 0, width, height);
}

void MyTimer(int Value) {

	// 화면을 다시 그렬줄 것을 명령한다.
	glutPostRedisplay();

	// 1번쨰 매개변수 : 얼마 후에 타이머를 실행 할 것인지
	// 2번째 매개변수 : 타이머 이벤트를 발생하기 위해서 호출되어야 할 함수
	// 3본째 매개변수 : 타이머 이벤트에게 넘겨주고 싶은 파라미터
	glutTimerFunc(5, MyTimer, NULL);
}

void initTexture()
{
	glGenTextures(3, texture);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("bitmap5.bmp", &width, &height, &nrChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	data = stbi_load("LAND2.BMP", &width, &height, &nrChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	data = stbi_load("bitmap4.bmp", &width, &height, &nrChannels, 0);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	stbi_image_free(data);
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100); // 실행창을 어디 위치에 보여줄지 표시해 준다.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // 디스플레이 표면의 특징을 결정한다.
	glutCreateWindow("OpenGL");

	initTexture(); // Texture mapping
	glutDisplayFunc(Display); // 그리기 전달함수 (인수는 그리기메서드)
	glutReshapeFunc(reshape_func); // 윈도우 크기를 조절할 때, 사용할 함수를 지정한다.
	glutKeyboardFunc(keyboard); // 키보드 입력
	glutSpecialFunc(Special); // 키보드의 특수 키 입력
	glutTimerFunc(0, MyTimer, NULL); // 선언된 이벤트를 무한으로 실행 시킨다.
	glutMainLoop();

	return 0;
}
