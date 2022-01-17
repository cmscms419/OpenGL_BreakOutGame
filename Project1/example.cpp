#include "model.h"


void draw(GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1);
		glVertex2f(-0.5, -0.5);
		glTexCoord2f(1, 1);
		glVertex2f(0.5, -0.5);
		glTexCoord2f(1, 0);
		glVertex2f(0.5, 0.5);
		glTexCoord2f(0, 0);
		glVertex2f(-0.5, 0.5);
	}
	glEnd();
    glDisable(GL_TEXTURE_2D);
}

void draw2()
{

}