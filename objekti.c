#include "objekti.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void iscrtaj_ose() 
{
    glBegin(GL_LINES);
        glColor3f(1, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(-1, 0, 0);

        glColor3f(0, 0, 1);
        glVertex3f(0, 1, 0);
        glVertex3f(0, -1, 0);

        glColor3f(0, 1, 0);
        glVertex3f(0, 0,  1);
        glVertex3f(0, 0, -1);

        float coef = 1.0/10;
        for (float i=-1; i < 1; i+= coef) {
            glColor3f(1, 0, 0);
            glVertex3f(i, -0.1*coef, 0);
            glVertex3f(i, +0.1*coef, 0);

            glColor3f(0, 0, 1);
            glVertex3f(-0.1*coef, i, 0);
            glVertex3f(+0.1*coef, i, 0);

            glColor3f(0, 1, 0);
            glVertex3f(-0.1*coef, 0, i);
            glVertex3f(+0.1*coef, 0, i);
        }

    glEnd();

}

void iscrtaj_pistolj()
{
    glPushMatrix();
    glColor3f(0, 0, 1);

    glPushMatrix();
        glScalef(0.2, 0.2, 1);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, -0.15, 0.5);
        glScalef(0.2, 0.5, 0.2);
        glutSolidCube(1);
    glPopMatrix();
    glPopMatrix();
}


void iscrtaj_metak() 
{
    glPushMatrix();
        glColor3f(1,0,0);
        const static GLdouble plane[] = { 0, 0, -1, 0 };
        glClipPlane(GL_CLIP_PLANE0, plane);
        glEnable(GL_CLIP_PLANE0);
        glScalef(0.1, 0.1, 0.15);
        glutSolidSphere(1, 30, 30);
        glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}
