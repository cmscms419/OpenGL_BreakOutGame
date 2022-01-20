#include "model.h"

void draw(GLuint texture)
{
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f(-0.5, 0.5);
		
		glTexCoord2f(1, 0);
		glVertex2f(0.5, 0.5);
		
		glTexCoord2f(1, 1);
		glVertex2f(0.5, -0.5);
		
		glTexCoord2f(0, 1);
		glVertex2f(-0.5, -0.5);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}