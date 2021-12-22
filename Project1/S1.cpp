#include "sourse.h"
#include "model.h"
#include <vector>

float rad = 0.5;

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float angle = i * 3.141592 / 180;
		float x = rad * cos(angle);
		float y = rad * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
	
	glFlush();
}

void reshape_func(int width, int height)
{
	glViewport(0, 0, width, height);
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB);
	glutCreateWindow("OpenGL");  // OpenGL ������ ���� (�μ��� Ÿ��Ʋ�� ����)
	glutDisplayFunc(Display);     // �׸��� �����Լ� (�μ��� �׸���޼���)
	glutReshapeFunc(reshape_func);
	glutMainLoop();

}