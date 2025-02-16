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
#include "tinyxml/tinyxml.h"

using namespace std;

//Variaveis
vector<vector<Triangle>> modelos_a_carregar; //Lista com os modelos a carregar

//Janela
int height = 0;
int width = 0;

//Posição
double pos_x = 0;
double pos_y = 0;
double pos_z = 0;

//Vetor de visão
double camera_x = 0;
double camera_y = 0;
double camera_z = 0;

//Vetor Normal
double normal_x = 0;
double normal_y = 0;
double normal_z = 0;

//Projeção
double fov = 0;
double near = 0;
double far = 0;

//Modo debug
bool modo_debug = false;
int quantidade_max_triangulos = 0;

// -------

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
	gluPerspective(fov,ratio,near,far);
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);

	// finally set the viewport to be the entire window
	glViewport(0, 0, w, h);
}

//Função que desenha
void renderScene(void) {

	//Iniciando a camera e posição ##########
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    gluLookAt(pos_x, pos_y, pos_z,  // Câmera ajustada
              camera_x, camera_y, camera_z,
              normal_x, normal_y, normal_z);

	//Eixos ##########
    glBegin(GL_LINES);

	//Eixo X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

	//Eixo Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

	//Eixo Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();

	//Desenhar figuras ##########
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_TRIANGLES);
    
	int i = 0;
	glColor3f(1,1,1);

    for (vector<Triangle> lista : modelos_a_carregar) {

		for (Triangle t : lista) {

			if (modo_debug == false || (modo_debug == true && i <= quantidade_max_triangulos)) {
			
				//Obter pontos
				Ponto a = t.p1;
				Ponto b = t.p2;
				Ponto c = t.p3;

				//Desenhar os pontos
	   			glVertex3f(a.x,a.y,a.z);
	   			glVertex3f(b.x,b.y,b.z);
	   			glVertex3f(c.x,c.y,c.z);

			}

			i++;

		}

    }
    
    glEnd();

    glutSwapBuffers();
}

//Função que processa as teclas especiais
void pressSpecialKey(int key, int x, int y) {
	/*
    switch (key) {
    case GLUT_KEY_UP:    angleX -= 5.0f; break;
    case GLUT_KEY_DOWN:  angleX += 5.0f; break;
    case GLUT_KEY_LEFT:  angleY -= 5.0f; break;
    case GLUT_KEY_RIGHT: angleY += 5.0f; break;
    }*/
	glutPostRedisplay();
}

//Função que processa as teclas normais
void pressKey(unsigned char key, int x, int y) {
    switch (key) {
    /*case '+': targetZoom -= 0.5f; break;
    case '-': targetZoom += 0.5f; break;*/

		//Modo debug
		case 'l':
			modo_debug = true;
			quantidade_max_triangulos = 0;
			break;
		
		//Aumentar a quantidade máxima de triangulos
		case 'k':
			quantidade_max_triangulos++;
			break;

    }

	glutPostRedisplay();
}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

int main(int argc, char** argv)
{
	//Inicialização
	height = 512;
	width = 512;

	//Posição
	pos_x = 3;
	pos_y = 2;
	pos_z = 1;

	//Vetor de visão
	camera_x = 0;
	camera_y = 0;
	camera_z = 0;

	//Vetor Normal
	normal_x = 0;
	normal_y = 1;
	normal_z = 0;

	//Projeção
	fov = 60;
	near = 1;
	far = 1000;


	// put GLUT init here
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
	glutInitWindowSize(width,height);
	glutCreateWindow("Projeto CG - 24/25");

	//Carregar os modelos
	for (int i = 1 ; i < argc ; i++) {
		vector<Triangle> novo_modelo_carregado = lerBinario(argv[i]);
		modelos_a_carregar.push_back(novo_modelo_carregado);
	}

	// put callback registry here
	glutKeyboardFunc(&pressKey);
	glutSpecialFunc(&pressSpecialKey);

	glutDisplayFunc(&renderScene);
	glutReshapeFunc(&changeSize);
	glutPostRedisplay();
	//glutIdleFunc(&renderScene);

	// some OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	// enter GLUT�s main cycle
	glutMainLoop();
	
	return 1;
}