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

using namespace std;

class Ponto {
    public:
        double x, y, z;

        // Construtor padrão necessário para o vetor funcionar corretamente
        Ponto() : x(0), y(0), z(0) {}

        // Construtor com parâmetros
        Ponto(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
};

class Triangle {
    public:
        Ponto p1, p2, p3;

        // Construtor padrão necessário para o vetor funcionar corretamente
        Triangle() : p1(), p2(), p3() {}

        // Construtor com parâmetros
        Triangle(Ponto p1, Ponto p2, Ponto p3) {
            this->p1 = p1;
            this->p2 = p2;
            this->p3 = p3;
        }
};

vector<Triangle> lista;

void lerBinario(const string& nomeArquivo) {
    ifstream f(nomeArquivo, ios::binary);
    if (!f) {
        cerr << "Erro ao abrir o arquivo para leitura!" << endl;
        return;
    }

    // Lendo o tamanho do vetor
    int tamanho;
    f.read(reinterpret_cast<char*>(&tamanho), sizeof(int));

    // Lendo os triângulos
    for (int i = 0; i < tamanho; i++) {
        double x1, y1, z1;
        f.read(reinterpret_cast<char*>(&x1), sizeof(double));
        f.read(reinterpret_cast<char*>(&y1), sizeof(double));
        f.read(reinterpret_cast<char*>(&z1), sizeof(double));

		double x2, y2, z2;
        f.read(reinterpret_cast<char*>(&x2), sizeof(double));
        f.read(reinterpret_cast<char*>(&y2), sizeof(double));
        f.read(reinterpret_cast<char*>(&z2), sizeof(double));

		double x3, y3, z3;
        f.read(reinterpret_cast<char*>(&x3), sizeof(double));
        f.read(reinterpret_cast<char*>(&y3), sizeof(double));
        f.read(reinterpret_cast<char*>(&z3), sizeof(double));

        lista.push_back(Triangle(Ponto(x1,y1,z1),Ponto(x2,y2,z2),Ponto(x3,y3,z3)));
    }

    f.close();
}


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

int i = 0;

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(3.0f, 2.0f, 1.0f,  // Câmera ajustada
              0.0f, 0.0f, 0.0f,
              0.0f, 1.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);  // Verde para o plano
    
    //CHAT
    glDisable(GL_CULL_FACE);

    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBegin(GL_TRIANGLES);
    
    for (Triangle t : lista) {

        glColor3f(1,1,1);

		Ponto a = t.p1;
		Ponto b = t.p2;
		Ponto c = t.p3;

		glVertex3f(a.x,a.y,a.z);
		glVertex3f(b.x,b.y,b.z);
		glVertex3f(c.x,c.y,c.z);

    }
    


    glEnd();

    glPushMatrix();
glRotatef(90, 1, 0, 0);  // Rotação de 90 graus no eixo X
glutWireSphere(1, 10, 10);
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


void pressKey(unsigned char key, int x, int y) {

	switch (key) {

		case 'w':
			i++;
		break;

	}

}

void printInfo() {

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
}

vector<Triangle> geraPlano(double size, double dimensoes) {
    vector<Triangle> lista;

    double inicio = -size / 2.0;
    double passo = size / dimensoes;

    for (int i = 0; i < dimensoes; i++) {
        for (int j = 0; j < dimensoes; j++) {

            double x0 = inicio + i * passo;
            double z0 = inicio + j * passo;
            double x1 = x0 + passo;
            double z1 = z0 + passo;

            // Criando dois triângulos para formar o quadrado
            Ponto p1(x0, 0.0, z0);
            Ponto p2(x1, 0.0, z0);
            Ponto p3(x0, 0.0, z1);

            Ponto p4(x1, 0.0, z1);

            lista.push_back(Triangle(p1, p2, p3)); // Primeiro triângulo
            lista.push_back(Triangle(p2, p4, p3)); // Segundo triângulo
        }
    }
    return lista;
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

	lerBinario("teste.3d");

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