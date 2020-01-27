#include "objekti.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include "image.h"
#include <string.h>

//Pravio sam sve objekte koje imam u igri
//Imena funkcija nam ukazuju o kojim objektima se radi

const float maks_brizna = 0.1;
const float korak_mete = 3;
float brzina_mete = 0.02;
float parametarPom = 0.1;//Parametar se koristi za rotaciju prepreka
Prepreka prepreke[MAX_PREPREKA];

GLuint wall_texture_name;

//Pomocna funkcija za iscrtavanje kordinatnog sistema
void iscrtaj_ose() {
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

//Funkcija koja sluzi za crtanje pistolja
void iscrtaj_pistolj() {
	//Koeficijenti ambijentalne refleksije materijala
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
	//Koeficijenti difuzne refleksije materijala    	
	GLfloat diffuse_coeffs[] = { 0.3, 0.3, 0.3, 1 };
	//Koeficijenti spekularne refleksije materijala
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	//Koeficijent glatkosti materijala
	GLfloat shininess = 0.3*128;
	
	/* Podesavaju se parametri materijala. */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);


	//Sredio sam izgled pistolja uz pomoc drugih tela
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
    	
	glPushMatrix();
        	glTranslatef(0, 0.04, 0.5);
        	glScalef(0.1, 0.2, 0.25);
        	glutSolidCube(1);
    	glPopMatrix();
    	
	glPushMatrix();
        	glTranslatef(0, 0.04, -0.43);
        	glScalef(0.03, 0.17, 0.07);
        	glutSolidCube(1);
    	glPopMatrix();
    	
	glPushMatrix();
        	glTranslatef(0, -0.1, 0.31);
        	glScalef(0.03, 0.17, 0.05);
        	glutSolidCube(1);
    	glPopMatrix();
    	
	glPushMatrix();
        	glTranslatef(0, -0.22, 0.5);
        	glScalef(0.22, 0.3, 0.15);
        	glutSolidCube(1);
    	glPopMatrix();
    	
	glPushMatrix();
		glTranslatef(0, 0.04, 0.05);
        	glScalef(0.22, 0.02, 1.1);
        	glutSolidCube(1);
    	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0, 0, 0.05);
        	glScalef(0.22, 0.02, 1.1);
        	glutSolidCube(1);
    	glPopMatrix();
	

	glPushMatrix();
		glTranslatef(0.1, -0.1, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
			
	glPushMatrix();
		glTranslatef(0.1, -0.15, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.1, -0.2, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
		
	glPushMatrix();
		glTranslatef(-0.1, -0.1, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
			
	glPushMatrix();
		glTranslatef(-0.1, -0.15, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-0.1, -0.2, 0.45);
		glutSolidSphere(0.025,16,16);
	glPopMatrix();
		
	
	glPopMatrix();
}

//Funkcija koja sluzi za crtanje metkova
void iscrtaj_metak() {
	//Koeficijenti ambijentalne refleksije materijala
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
	//Koeficijenti difuzne refleksije materijala
	GLfloat diffuse_coeffs[] = { 1.0, 0.6, 0.1, 1 };
	//Koeficijenti spekularne refleksije materijala
	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	//Koeficijent glatkosti materijala	
	GLfloat shininess = 0.3*128;
	
	/* Podesavaju se parametri materijala. */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	//Sredio sam izgled metka koristeci sferu i clipping ravan
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


//Funkcija za pravljenje prepreka
Prepreka napravi_prepreke(){
	Prepreka tmp;
    	tmp.x =  -10; //Polozaj po x osi
    	tmp.z = -5; //Polozaj po y osi
        tmp.pogodjena_parametar = 0; 
        tmp.is_pogodjena = false; //inicijalno, telo nije pogodjeno
	tmp.pogodjena_parametar1 = 1;
    
    	return tmp;
}

//Funkcija koja pravi niz prepreka, max_prepreka je 30
void inicijalizuj_prepreke(){
	for(int i = 0; i < MAX_PREPREKA; i++) {
        	prepreke[i] = napravi_prepreke();
        	prepreke[i].x = prepreke[i].x + korak_mete * i;
    	}
}

//Funkcija koja azurira prepreke po x osi, menja brzinu prepreke
void azuriraj_prepreke(){
	int i;

	if(brzina_mete < 0.1)
		brzina_mete += 0.00008;

	for (i = 0; i < MAX_PREPREKA; i++) {
        	prepreke[i].x -= brzina_mete;
	}
}

//Funkcija za crtanje prereka
void nacrtaj_prepreke() {
	//Koeficijenti ambijentalne refleksije materijala
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
	//Koeficijenti difuzne refleksije materijala
    	GLfloat diffuse_coeffs[] = { 0.1, 0.4, 1, 1 };
	//Koeficijenti spekularne refleksije materijala
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	//Koeficijent glatkosti materijala	
	GLfloat shininess = 0.3*128;
	
	/* Podesavaju se parametri materijala. */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	for(int i=0;i<MAX_PREPREKA;i++){
		//Ako prepreka nije pogodjenja
        	if (!prepreke[i].is_pogodjena) {
            	glPushMatrix();
                	glTranslatef(prepreke[i].x, 0,prepreke[i].z );//Kretanje prepreke kad se pogodi
                	glutSolidCube(0.3);//Crtanje kocke
			glutSolidSphere(0.17,15,15);//Crtamo sferu
			glutWireCone(0.24, 0.24, 15, 1);//Crtamo kupu
			glRotatef(parametarPom*10, 1,0,0);//Rotacija ikosaedra po x osi
			glScalef(0.3, 0.3, 0.3);//Skaliranje ikosaedra
			glutWireIcosahedron();//Crtanje ikosaedra
			parametarPom += 0.01;//Parametar za rotaciju
      		glPopMatrix();
        	}
		//Ako prepreka jeste pogodjena
		else {
		        if (prepreke[i].pogodjena_parametar <= 1) {
		            glPushMatrix();
		                glTranslatef(prepreke[i].x, -prepreke[i].pogodjena_parametar*5,prepreke[i].z );//Kretanje prepreke kad se pogodi
				glRotatef(prepreke[i].pogodjena_parametar*193, 1,0,1);//Rotacija prepreke po x i z osi
		                glutSolidCube(0.3*prepreke[i].pogodjena_parametar1);//Crtamo kocku
				glutSolidSphere(0.17*prepreke[i].pogodjena_parametar1,15,15);//Crtamo sferu
				glutWireCone(0.24*prepreke[i].pogodjena_parametar1, 0.24, 15, 1);//Crtamo kupu
				glRotatef(parametarPom*10, 1,0,0);//Rotacija ikosaedra
				glScalef(0.3*prepreke[i].pogodjena_parametar1, 0.3*prepreke[i].pogodjena_parametar1, 0.3*prepreke[i].pogodjena_parametar1);//Skaliranje ikosaedra
				glutWireIcosahedron();//Crtamo ikosaedar

				if(prepreke[i].pogodjena_parametar1>0){
					prepreke[i].pogodjena_parametar1-=0.005;//Parametar za smanjivanje prepreke kada se pogodi
				}

				parametarPom += 0.01;//Parametar za rotaciju
		                prepreke[i].pogodjena_parametar += 0.01;//Parametar za rotaciju kada je prepreka pogodjena 
		            glPopMatrix();
		        }	
		}
	}
}

//Sto se tice tekstura, koristio sam kodove sa vezbi, naravno uz izmene i prilagodjeno projektu
void initialize()
{
    /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
    Image * image;

    /* Postavlja se boja pozadine. */
    glClearColor(0, 0, 0, 0);

    /* Ukljucuje se testiranje z-koordinate piksela. */
    glEnable(GL_DEPTH_TEST);

    /* Ukljucuju se teksture. */
    glEnable(GL_TEXTURE_2D);

    glTexEnvf(GL_TEXTURE_ENV,
              GL_TEXTURE_ENV_MODE,
              GL_REPLACE);

    /*
     * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
     * fajla.
     */
    image = image_init(0, 0);

    /* Kreira se prva tekstura. */
    image_read(image, "images.bmp");

    /* Generisu se identifikatori tekstura. */
    glGenTextures(1, &wall_texture_name);

    glBindTexture(GL_TEXTURE_2D, wall_texture_name);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 image->width, image->height, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    /* Iskljucujemo aktivnu teksturu */
    glBindTexture(GL_TEXTURE_2D, 0);

    /* Unistava se objekat za citanje tekstura iz fajla. */
    image_done(image);
}


//Funkcija za crtanje zida
void iscrtaj_zid(){
	const static GLfloat material_emission[] = { 0.15, 0.15, 0.15, 1 };
    	
	//Koeficijenti ambijentalne refleksije materijala
	GLfloat ambient_coeffs[] = { 0.05375, 0.05, 0.06625, 1 };
	//Koeficijenti difuzne refleksije materijala
    	GLfloat diffuse_coeffs[] = { 0.6, 0.6, 0.6, 1 };
	//Koeficijenti spekularne refleksije materijala
    	GLfloat specular_coeffs[] = {  0.332741, 0.528634, 0.346435, 1 };
	//Koeficijent glatkosti materijala
	GLfloat shininess = 0.3*128;
	
	/* Podesavaju se parametri materijala. */
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_coeffs);
    	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_coeffs);
    	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	
	glMaterialfv(GL_FRONT, GL_EMISSION, material_emission);

	//Crtanje poligona
	glPushMatrix();
		glBegin(GL_QUADS);

		    glColor3f(1, 0, 0);
		    glNormal3f(0, 0, 1);

		    glTexCoord2f(0 ,1);
		    	glVertex3f(-0.5, 0.5, 0);

		    glTexCoord2f(1 ,1);
			glVertex3f(0.5, 0.5, 0);

		    glTexCoord2f(1 ,0);
			glVertex3f(0.5, -0.5, 0);

		    glTexCoord2f(0 ,0);
			glVertex3f(-0.5, -0.5, 0);

		glEnd();
	glPopMatrix();
}

//Funkcija za ispis teksta 
void ispisi_tekst(char * tekst, int x, int y, float r, float g, float b, int sirina_ekrana, int duzina_ekrana)
{
	glDisable(GL_LIGHTING);

    	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
   	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	//Boja teksta
	glColor4f(r, g, b, 1.0 );
	glOrtho(0, sirina_ekrana, 0, duzina_ekrana, -1, 1);

	glRasterPos2f(x, y);

	//Ispis teksta karak. po karak.
	int len= strlen(tekst);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, tekst[i]);
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

