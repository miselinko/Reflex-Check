#include "objekti.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>

const float maks_brizna = 0.1;
const float korak_mete = 3;
float brzina_mete = 0.02;
Prepreka prepreke[MAX_PREPREKA];

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
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 0.3, 0.3, 0.3, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	GLfloat shininess = 0.3*128;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 1.0, 0.3, 0.2, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	GLfloat shininess = 0.3*128;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

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

Prepreka napravi_prepreke(){
	Prepreka tmp;
    	tmp.x =  -10;
    	tmp.z = -5;
    
    	return tmp;
}

void inicijalizuj_prepreke(){
	for(int i = 0; i < MAX_PREPREKA; i++) {
        	prepreke[i] = napravi_prepreke();
        	prepreke[i].x = prepreke[i].x + korak_mete * i;
    	}
}

void azuriraj_prepreke(){
	int i;

	if(brzina_mete < 0.1)
		brzina_mete += 0.0001;

	for (i = 0; i < MAX_PREPREKA; i++) {
        	prepreke[i].x -= brzina_mete;
	}
}

void nacrtaj_prepreke(){
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 0.3, 0.3, 1, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	GLfloat shininess = 0.3*128;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	for(int i=0;i<MAX_PREPREKA;i++){
		glPushMatrix();
			glTranslatef(prepreke[i].x, 0,prepreke[i].z );
            		glutSolidCube(0.25);
      		glPopMatrix();
	}
}

void iscrtaj_zid(){
	const static GLfloat material_emission[] = { 0.2, 0.2, 0.2, 1 };
    	
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
    	GLfloat diffuse_coeffs[] = { 0.8, 0.1, 0.8, 1 };
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	GLfloat shininess = 0.3*128;
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);

	glPushMatrix();
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glNormal3f(0, 0, 1);
        glVertex3f(-0.5, 0.5, 0);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(0.5, -0.5, 0);
        glVertex3f(-0.5, -0.5, 0);
	glEnd();
	glPopMatrix();

}
