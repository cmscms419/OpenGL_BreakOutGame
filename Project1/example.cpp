#include "model.h"


void draw(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-0.5, 0.5);
		glTexCoord2f(0, 1);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1, 1);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1, 0);
		glVertex2f(0.5, 0.5);
	}
	glEnd();

}

void draw2()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
    glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
    glVertex3f(1.0f, -1.0f, 1.0f); // { Front }

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
    glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
    glVertex3f(1.0f, -1.0f, -1.0f); // { Right }

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
    glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
    glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 1.0f, 0.0f); // { Left }
    glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
    glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
    glEnd();
}