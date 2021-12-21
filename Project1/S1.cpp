#include "sourse.h"

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0, 0.5);
	glVertex2f(-0.5, -0.5);
	glVertex2f(0.5, -0.5);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL");  // OpenGL ������ ���� (�μ��� Ÿ��Ʋ�� ����)
	glutDisplayFunc(Display);     // �׸��� �����Լ� (�μ��� �׸���޼���)
	glutMainLoop();

}