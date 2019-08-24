#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "objekti.h"

static void on_display();
static void on_reshape(int width, int height);
static void on_key_press(unsigned char key, int x, int y);

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutInitWindowPosition(100, 100);

	glutCreateWindow("Titl programa");

	glutDisplayFunc(on_display);
	glutReshapeFunc(on_reshape);
	glutKeyboardFunc(on_key_press);

	glClearColor(1, 1, 1, 0);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;
}

static void on_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(3, 2, 1, 0, 0, 0, 0, 1, 0);

    iscrtaj_ose();

	glutSwapBuffers();
}

static void on_reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (float) width / height, 0.1, 1500);
}

static void on_key_press(unsigned char key, int x, int y)
{
	switch (key) {
        case 27:
			exit(EXIT_SUCCESS);
			break;
	}
}

