#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

#define CRT_SECURE_NO_WARNINGS

#define	WIRE 0		
#define	SHADE 1
#define PER 1

GLfloat light_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };  /* Red diffuse light. */
GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };  /* Infinite light location. */
GLfloat	light_specular[] = { 1.0, 1.0, 1.0, 1.0 }; /* specular light */
GLfloat	light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };  /* ambient light */

typedef struct {
	float x;
	float y;
	float z;
} Point;

typedef struct {
	float x;
	float y;
	float z;
	float a;
	float b;
} Point_ply;

typedef struct {
	unsigned long ip[3];
} Face;

int pnum;
int fnum;
Point* mpoint;
Point_ply* mpoint_ply;
Face* mface;

GLfloat anglex = -150;   /* in degrees */
GLfloat angley = -150;   /* in degrees */


GLfloat light_angle1 = -150;   /* in degrees */
GLfloat light_angle2 = -150;   /* in degrees */


GLfloat xloc = 0, yloc = 0, zloc = 0;
int moving;
int beginx, beginy;
int light_moving;
float scalefactor = 1.0;
int scaling = 0;
int status = 0;           // WIRE or SHADE
int cull = 0;             // CULLING toggle 
char* fname = "cube.dat";

void DrawWire(void)
{
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glCallList(1);
	glutSwapBuffers();
}

void DrawShade(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	if (cull) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glCallList(1);
	glutSwapBuffers();
}

Point cnormal(Point a, Point b, Point c)
{
	Point p, q, r;
	double val;
	p.x = a.x - b.x; p.y = a.y - b.y; p.z = a.z - b.z;
	q.x = c.x - b.x; q.y = c.y - b.y; q.z = c.z - b.z;

	r.x = p.y * q.z - p.z * q.y;
	r.y = p.z * q.x - p.x * q.z;
	r.z = p.x * q.y - p.y * q.x;

	val = sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
	r.x = r.x / val;
	r.y = r.y / val;
	r.z = r.z / val;
	return r;
}

void MakeGL_Model(void)
{
	int i;
	Point norm;
	glShadeModel(GL_SMOOTH);

	glPushMatrix();
	glRotatef(light_angle1, 0.0, 1.0, 0.0);
	glRotatef(light_angle2, 1.0, 0.0, 0.0);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	if (glIsList(1)) glDeleteLists(1, 1);
	glNewList(1, GL_COMPILE);
	glPushMatrix();
	glTranslatef(xloc, yloc, zloc);
	glRotatef(anglex, 0.0, 1.0, 0.0);
	glRotatef(angley, 1.0, 0.0, 0.0);
	glScalef(scalefactor, scalefactor, scalefactor);
	for (i = 0; i < fnum; i++) {
		norm = cnormal(mpoint[mface[i].ip[2]], mpoint[mface[i].ip[1]],
			mpoint[mface[i].ip[0]]);
		glBegin(GL_TRIANGLES);
		glNormal3f(norm.x, norm.y, norm.z);
		glVertex3f(mpoint[mface[i].ip[0]].x, mpoint[mface[i].ip[0]].y,
			mpoint[mface[i].ip[0]].z);
		glVertex3f(mpoint[mface[i].ip[1]].x, mpoint[mface[i].ip[1]].y,
			mpoint[mface[i].ip[1]].z);
		glVertex3f(mpoint[mface[i].ip[2]].x, mpoint[mface[i].ip[2]].y,
			mpoint[mface[i].ip[2]].z);
		glEnd();
	}
	glPopMatrix();
	glEndList();
}

void GLSetupRC(void)
{
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);


	/* Use depth buffering for hidden surface elimination. */
	glEnable(GL_DEPTH_TEST);

	/* Setup the view */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(40.0, // field of view in degree 
		1.0, // aspect ratio 
		1.0, // Z near 
		2000.0); // Z far 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		400.0 + xloc, 400.0 + yloc, 400.0 + zloc,  // eye is at (0,0,5) 
		0.0, 0.0, 0.0,      // center is at (0,0,0) 
		0.0, 1.0, 0.);      // up is in positive Y direction 
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	MakeGL_Model();
	if (status == WIRE) DrawWire();
	else DrawShade();
}

void ReadModel_ply()
{
	FILE* f1;
	char s[81];
	int num;

	int i;

	if ((f1 = fopen(fname, "rt")) == NULL) {
		printf("No file\n");
		exit(0);
	}
	fscanf(f1, "%s", s);     printf("%s ", s);
	fscanf(f1, "%s", s);     printf("%s ", s);
	fscanf(f1, "%d", &pnum);     printf("%d\n", pnum);

	mpoint_ply = (Point_ply*)malloc(sizeof(Point_ply) * pnum);

	for (i = 0; i < pnum; i++) {
		fscanf(f1, "%f", &mpoint_ply[i].x);
		fscanf(f1, "%f", &mpoint_ply[i].y);
		fscanf(f1, "%f", &mpoint_ply[i].z);
		fscanf(f1, "%f", &mpoint_ply[i].a);
		fscanf(f1, "%f", &mpoint_ply[i].b);
		printf("%f %f %f %f %f\n", mpoint_ply[i].x, mpoint_ply[i].y, mpoint_ply[i].z, mpoint_ply[i].a, mpoint_ply[i].b);
	}

	fscanf(f1, "%s", s);     printf("%s ", s);
	fscanf(f1, "%s", s);     printf("%s ", s);
	fscanf(f1, "%d", &fnum);     printf("%d\n", fnum);

	mface = (Face*)malloc(sizeof(Face) * fnum);
	for (i = 0; i < fnum; i++) {
		fscanf(f1, "%d", &num);
		fscanf(f1, " %d", &mface[i].ip[0]);
		fscanf(f1, " %d", &mface[i].ip[1]);
		fscanf(f1, " %d", &mface[i].ip[2]);
		printf(" %d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}
	fclose(f1);
}

void ReadModel()
{
	FILE* f1;
	char s[81];

	int i;

	if ((f1 = fopen(fname, "rt")) == NULL) {
		printf("No file\n");
		exit(0);
	}
	fscanf(f1, "%s", s);     printf("%s", s);
	fscanf(f1, "%s", s);     printf("%s", s);
	fscanf(f1, "%d", &pnum);     printf("%d\n", pnum);

	mpoint = (Point*)malloc(sizeof(Point) * pnum);

	for (i = 0; i < pnum; i++) {
		fscanf(f1, "%f", &mpoint[i].x);
		fscanf(f1, "%f", &mpoint[i].y);
		fscanf(f1, "%f", &mpoint[i].z);
		printf("%f %f %f\n", mpoint[i].x, mpoint[i].y, mpoint[i].z);
	}

	fscanf(f1, "%s", s);     printf("%s", s);
	fscanf(f1, "%s", s);     printf("%s", s);
	fscanf(f1, "%d", &fnum);     printf("%d\n", fnum);

	mface = (Face*)malloc(sizeof(Face) * fnum);
	for (i = 0; i < fnum; i++) {
		fscanf(f1, "%d", &mface[i].ip[0]);
		fscanf(f1, "%d", &mface[i].ip[1]);
		fscanf(f1, "%d", &mface[i].ip[2]);
		printf("%d %d %d\n", mface[i].ip[0], mface[i].ip[1], mface[i].ip[2]);
	}
	fclose(f1);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		moving = 1;
		beginx = x;
		beginy = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		moving = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
		scaling = 1;
		beginx = x;
		beginy = y;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		scaling = 0;
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		scaling = 0;
		light_moving = 1;
		beginx = x;
		beginy = y;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
		light_moving = 0;
	}
}

void motion(int x, int y)
{
	if (scaling) {
		scalefactor = scalefactor * (1.0 + (beginx - x) * 0.0001);
		glutPostRedisplay();
	}
	if (moving) {
		anglex = anglex + (x - beginx);
		angley = angley + (beginy - y);
		beginx = x;
		beginy = y;
		glutPostRedisplay();
	}
	if (light_moving) {
		light_angle1 = light_angle1 + (x - beginx);
		light_angle2 = light_angle2 + (beginx - y);
		beginx = x;
		beginy = y;
		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y)
{
	printf("key %d\n", key);

	switch (key)
	{
	case 'w':
		status = WIRE;
		glutPostRedisplay();
		break;
	case 's':
		status = SHADE;
		glutPostRedisplay();
		break;
	case 'c':
		if (cull) cull = 0;
		else cull = 1;
		glutPostRedisplay();
		break;
	case '1':
		fname = "cube.dat";
		ReadModel();
		glutPostRedisplay();
		break;
	case '2':
		fname = "sphere.dat";
		ReadModel();
		glutPostRedisplay();
		break;
	case '3':
		fname = "teapot.dat";
		ReadModel();
		glutPostRedisplay();
		break;
	case '4':
		fname = "plance.dat";
		ReadModel();
		glutPostRedisplay();
		break;
	case '5':
		fname = "house.dat";
		ReadModel();
		glutPostRedisplay();
		break;
	case '6':
		fname = "bun_zipper_res4.ply";
		ReadModel_ply();
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void keyboard_udrf(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		glTranslatef(0, PER, 0);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		glTranslatef(0, -PER, 0);
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		glTranslatef(-PER, 0, PER);
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		glTranslatef(PER, 0, -PER);
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Simple Modeling");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutSpecialFunc(keyboard_udrf);
	ReadModel();
	GLSetupRC();
	glutMainLoop();
	return 0;             /* ANSI C requires main to return int. */
}