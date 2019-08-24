#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "objekti.h"

static void on_display();
static void on_reshape(int width, int height);
static void on_key_press(unsigned char key, int x, int y);
static void on_key_release(unsigned char key, int x, int y);
static void on_mouse_move(int x, int y);
static void on_timer(int timer_id);

#define MAX_METKOVA (255)
Metak metkovi[MAX_METKOVA];
int br_ispaljeniih_metaka=0;

#define MAX_PREPREKA (255)
Metak prepreke[MAX_PREPREKA];
int br_poslatih_prepreka=0;

/* GLOBALNE PROMENLJIVE */

float pozicija = 0.0f;

bool go_left = false;
bool go_right = false;

int old_x_pos = 0;
int old_y_pos = 0;

int timer_id = 0;
int timer_interval = 15;

int screen_width = 0;
int screen_height = 0;

float cooldown = 0;


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
	glutKeyboardUpFunc(on_key_release);
    /*glutPassiveMotionFunc(on_mouse_move);*/
    /*glutMotionFunc(on_mouse_move);*/
    glutTimerFunc(timer_interval, on_timer, timer_id);

	glClearColor(1, 1, 1, 0);

	glEnable(GL_DEPTH_TEST);


    // Inicijalizacija metova i prepreka
    for (int i=0; i < MAX_METKOVA; i++) {
        metkovi[i].x = 0;
        metkovi[i].z = -0.5;

    }

	glutMainLoop();

	return 0;
}

static void on_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 2, 0, 0, 0, 0, 1, 0);

    iscrtaj_ose();
    
    glPushMatrix();
        glTranslatef(pozicija, 0, 0);
        iscrtaj_pistolj();
    glPopMatrix();

    for (int i=0; i < br_ispaljeniih_metaka; i++) {
        glPushMatrix();
            glTranslatef(metkovi[i].x,0,metkovi[i].z);
            iscrtaj_metak();
        glPopMatrix();
    }

	glutSwapBuffers();
}

static void on_reshape(int width, int height)
{
	glViewport(0, 0, width, height);
    screen_width = width;
    screen_height = height;

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
        case 'a':
        case 'A':
            go_left = true;
            break;
        case 'd':
        case 'D':
            go_right = true;
            break;
        case 'g':
        case 'G':
            if (cooldown == 0) {
                metkovi[br_ispaljeniih_metaka++].x = pozicija;
                cooldown = 50;
            }
            break;
	}
}


static void on_key_release(unsigned char key, int x, int y) {

	switch (key) {
        case 'a':
        case 'A':
            go_left = false;
            break;
        case 'd':
        case 'D':
            go_right = false;
            break;
	}

}


static void on_mouse_move(int x, int y) 
{
    static const float tmp = 0.01;
    int delta_x = old_x_pos - x;
    pozicija += delta_x * tmp;
    old_y_pos = y;
}


static void on_timer(int id) {
    if (id != timer_id)
        return;

    float parametar = 0.01;
    if (go_left && !go_right) {
        if (pozicija > -1.0)
            pozicija -= parametar;
    } else if (go_right && !go_left) {
        if (pozicija < 1.0)
            pozicija += parametar;
    }

    for (int i=0; i < br_ispaljeniih_metaka; i++) {
        if (metkovi[i].z > -100.0)
            metkovi[i].z -= 0.02;
    }

    if (cooldown > 0)
        cooldown -= 1;

    glutPostRedisplay();
    glutTimerFunc(timer_interval, on_timer, timer_id);
}
