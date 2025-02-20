
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
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
#include "engine/World.h"

#include "engine/processaXML.h"

using namespace std;

World world;

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
	gluPerspective(world.fov,ratio,world.near,world.far);
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
    gluLookAt(world.pos_x, world.pos_y, world.pos_z,  // Câmera ajustada
              world.camera_x, world.camera_y, world.camera_z,
              world.normal_x, world.normal_y, world.normal_z);

	glRotatef(world.angle_x, 1.0f, 0.0f, 0.0f);
	glRotatef(world.angle_y, 0.0f, 1.0f, 0.0f);
	glRotatef(world.angle_z, 0.0f, 0.0f, 1.0f);

	//Eixos ##########
    glBegin(GL_LINES);

	//Eixo X
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

	// //Eixo Y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

	// //Eixo Z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);

    glEnd();

	//glDisable(GL_CULL_FACE);
	//Desenhar figuras ##########
    glPolygonMode(GL_FRONT, GL_LINE);
    glBegin(GL_TRIANGLES);

	int i = 0;
	glColor3f(1,1,1);
	
	for (vector<Triangle> lista : world.modelos_a_carregar) {

		for (Triangle t : lista) {

			if (world.modo_debug == false || (world.modo_debug == true && i <= world.quantidade_max_triangulos)) {
			
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
	
    switch (key) {
    case GLUT_KEY_UP:    world.angle_x -= 5.0f; break;
    case GLUT_KEY_DOWN:  world.angle_x += 5.0f; break;
    case GLUT_KEY_LEFT:  world.angle_y -= 5.0f; break;
    case GLUT_KEY_RIGHT: world.angle_y += 5.0f; break;
    }
	glutPostRedisplay();
}

//Função que processa as teclas normais
void pressKey(unsigned char key, int x, int y) {
    switch (key) {
    case '+': world.angle_z += 5.0f; break;
    case '-': world.angle_z -= 5.0f; break;

		//Modo debug
		case 'l':
			world.modo_debug = true;
			world.quantidade_max_triangulos = 0;
			break;
		
		//Aumentar a quantidade máxima de triangulos
		case 'k':
			world.quantidade_max_triangulos++;
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

	//Não há argumentos suficientes
	if (argc < 2) {

		cerr << "Argumentos em falta\n";
		cerr << "USO : ./engine [CAMINHO PARA XML]\n";

		return 1;

	}
	//Há argumentos suficientes
	else {

		//Inicializar mundo
		world = World();

		//Ler dados do xml
		TiXmlDocument xml(argv[1]);

		//XML falhou
		if (xml.LoadFile() == false) {

			cerr << "Erro ao carregar o ficheiro XML\n";
			return 2;

		}

		//Processar XML - correu bem
		if (processaXML(world,xml)) {

			// put GLUT init here
			glutInit(&argc,argv);
			glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    		glutInitWindowPosition(100,100);
			glutInitWindowSize(world.width,world.height);
			glutCreateWindow("Projeto CG - 24/25");


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

			return 0;

		}
		else {

			cerr << "Ficheiro XML não foi corretamente processado\n";
			return 1;

		}

	}

}
