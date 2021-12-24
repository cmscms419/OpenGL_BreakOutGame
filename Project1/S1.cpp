#include "sourse.h"
#include "model.h"
#include <vector>

#define PI 3.141592

double radius = 0.2;

double angle = 3.141592 / 180;

GLfloat x = 0.0, y = 0.0; // 원의 초기 위치 값
GLfloat dx = 0.01, dy = 0.01; // 원의 이동 크기(속도)
GLfloat xDir = 1, yDir = 1.3; // 이동 방향

void Circle(GLfloat cx, GLfloat cy)
{
	float x1, y1, x2, y2;
	float angle;
	double rad = radius;

	x1 = cx, y1 = cy;

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

void move()
{
	x += xDir * dx;
	y += yDir * dy;

	// 원이 화면 범위를 벗어나게 되면 -1를 곱해서 방향을 바꾼다.
	// 원의 이동 범위는 -1 ~ 1이다.
	if ((xDir < 0 && x < -0.8) || (xDir > 0 && x > 0.8))
	{
		xDir = -xDir;
	}
	if ((yDir < 0 && y < -0.8) || (yDir > 0 && y > 0.8))
	{ 
		yDir = -yDir;
	}
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT); // 전에 있는 원의 흔적을 지운다.

	Circle(x + dx, y + dy);
	move();

	glutSwapBuffers();
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100); // 실행창을 어디 위치에 보여줄지 표시해 준다.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // 디스플레이 표면의 특징을 결정한다.
	glutCreateWindow("OpenGL");

	glutDisplayFunc(Display); // 그리기 전달함수 (인수는 그리기메서드)
	glutReshapeFunc(reshape_func); // 윈도우 크기를 조절할 때, 사용할 함수를 지정한다.
	glutTimerFunc(0, MyTimer, NULL); // 선언된 이벤트를 무한으로 실행 시킨다.
	glutMainLoop();

	return 0;
}