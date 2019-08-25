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
static void on_timer1(int id);

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

int animation_ongoing = 0;

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

	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1 };
	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	GLfloat light_specular[] = { 1, 1, 1, 1 };

	// Ambijentalno osvetljenje scene. /
	GLfloat model_ambient[] = { 0.5, 0.5, 0.5, 1 };

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_position[] = { 1, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);

	// Normalizacija normala /
	glEnable(GL_NORMALIZE);

	// Pozicionira se svijetlo. /
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);	

    // Inicijalizacija metova i prepreka
    for (int i=0; i < MAX_METKOVA; i++) {
        metkovi[i].x = 0;
        metkovi[i].z = -0.5;

    }

	inicijalizuj_prepreke();

	glutMainLoop();

	return 0;
}

static void on_display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 2, 0, 0, 0, 0, 1, 0);

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
	nacrtaj_prepreke();
	
	glPushMatrix();
		glScalef(1000, 1000, 1);
		glTranslatef(0, 0, -20);
		iscrtaj_zid();
	glPopMatrix();
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
	case 'k':
	case 'K':
		animation_ongoing=1;
		glutTimerFunc(17, on_timer1, 0);
		glutPostRedisplay();
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
            metkovi[i].z -= 0.1;
    }

    if (cooldown > 0)
        cooldown -= 1;

    glutPostRedisplay();
    glutTimerFunc(timer_interval, on_timer, timer_id);
}

static void on_timer1(int id){
	if(id != 0)
		return;

	azuriraj_prepreke();
	//glutTimerFunc(50, on_timer1, 0);
	if(animation_ongoing)
		glutTimerFunc(17, on_timer1, 0);
}
