#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"

using namespace std;

vector<Triangle> lista;


void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you can�t make a window with zero width).
	if (h == 0)
		h = 1;
	// compute window's aspect ratio
	float ratio = w * 1.0f / h;
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// finally set the viewport to be the entire window
	glViewport(0, 0, w, h);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0f, 2.0f, 1.0f,  // Câmera ajustada
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);  // Verde para o plano
    
    //CHAT
    //glDisable(GL_CULL_FACE);

    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    
    for (Triangle t : lista) {

        glColor3f(1,1,1);

		Ponto a = t.p1;
		Ponto b = t.p2;
		Ponto c = t.p3;

        /*
        
        TESTAR POSIÇÃO
        
        */

		glVertex3f(a.x,a.y,a.z);
		glVertex3f(b.x,b.y,b.z);
		glVertex3f(c.x,c.y,c.z);

    }
    


    glEnd();

    glPushMatrix();
glRotatef(90, 1, 0, 0);  // Rotação de 90 graus no eixo X
//glutWireSphere(1, 10, 10);
glPopMatrix();

    // Eixos para referência
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); // Eixo X vermelho
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f); // Eixo Y verde
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f); // Eixo Z azul
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    glutSwapBuffers();
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv)
{
	//Nota : trabalho em modo release

	// put GLUT init here
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
	glutInitWindowSize(800,800);
	glutCreateWindow("Janela");

	// put callback registry here
    //glutKeyboardFunc(&pressKey);

	lista = lerBinario(argv[1]);

	glutDisplayFunc(&renderScene);
	glutReshapeFunc(&changeSize);
	glutIdleFunc(&renderScene);
	
	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUT�s main cycle
	glutMainLoop();
	
	return 1;
}