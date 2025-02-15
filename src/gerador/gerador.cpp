#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"
#include <math.h>

using namespace std;

vector<Triangle> geraEsfera(double radius, double slides, double stacks) {

    vector<Triangle> lista;

    for (int i = 0; i < stacks; ++i) {
        float phi1 = M_PI * i / stacks;
        float phi2 = M_PI * (i + 1) / stacks;

        for (int j = 0; j < slides; ++j) {
            float theta1 = 2.0f * M_PI * j / slides;
            float theta2 = 2.0f * M_PI * (j + 1) / slides;

            float x1 = radius * sin(phi1) * cos(theta1);
            float y1 = radius * cos(phi1);
            float z1 = radius * sin(phi1) * sin(theta1);

            float x2 = radius * sin(phi2) * cos(theta1);
            float y2 = radius * cos(phi2);
            float z2 = radius * sin(phi2) * sin(theta1);

            float x3 = radius * sin(phi1) * cos(theta2);
            float y3 = radius * cos(phi1);
            float z3 = radius * sin(phi1) * sin(theta2);

            float x4 = radius * sin(phi2) * cos(theta2);
            float y4 = radius * cos(phi2);
            float z4 = radius * sin(phi2) * sin(theta2);

            Ponto p1 = Ponto(x1,y1,z1);
            Ponto p2 = Ponto(x2,y2,z2);
            Ponto p3 = Ponto(x3,y3,z3);
            Ponto p4 = Ponto(x4,y4,z4);

            lista.push_back(Triangle(p1,p2,p3));
            lista.push_back(Triangle(p2,p4,p3));
        }
    }

    return lista;

}

vector<Triangle> geraCaixa(double length, double divisions) {

    //TODO:
    vector<Triangle> lista;
    return lista;

}

vector<Triangle> geraCone(double radius, double height, double slices, double stacks) {

    //TODO:
    vector<Triangle> lista;
    return lista;

}

vector<Triangle> geraPlano(double length, double divisions) {

    vector<Triangle> lista;

    double inicio = length/2;
    double salto = length / divisions;

    for (int i = 0; i < divisions; i++) {

        for (int j = 0; j < divisions ; j++) {

            double ponto_inicial_x = -inicio;
            ponto_inicial_x += (i*salto);

            double ponto_inicial_z = -inicio;
            ponto_inicial_z += (j*salto);

            Ponto p1_1 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z + salto);
            Ponto p1_2 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z);
            Ponto p1_3 = Ponto(ponto_inicial_x,0,ponto_inicial_z);
            
            Ponto p2_1 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z + salto);
            Ponto p2_2 = Ponto(ponto_inicial_x,0,ponto_inicial_z);
            Ponto p2_3 = Ponto(ponto_inicial_x,0,ponto_inicial_z + salto);

            lista.push_back(Triangle(p1_1,p1_2,p1_3));
            lista.push_back(Triangle(p2_1,p2_2,p2_3));

        }

    }

    return lista;

}

//Main do Gerador
int main(int argn, char** argv) {

    const char* uso_sphere = "./generator sphere [RAIO] [SLICES] [STACKS] [NOME DO FICHEIRO]\n";
    const char* uso_box = "./generator box [TAMANHO] [DIVISÃO] [NOME DO FICHEIRO]\n";
    const char* uso_cone = "./generator cone [RAIO] [ALTURA] [SLICES] [STACKS] [NOME DO FICHEIRO]\n";
    const char* uso_plane = "./generator plane [TAMANHO] [DIVISÕES] [NOME DO FICHEIRO]\n";

    if (argn < 2) {
        cerr << "Argumentos inválidos!\n";
        cerr << "USO:\n";
        cerr << uso_sphere;
        cerr << uso_box;
        cerr << uso_cone;
        cerr << uso_plane;

        return 1;
    }

    //Esfera
    if (strcmp(argv[1],"sphere") == 0) {

        if (argn >= 6) {

            double radius = strtod(argv[2],nullptr);
            double slides = strtod(argv[3],nullptr);
            double stacks = strtod(argv[4],nullptr);
            escreverBinario(argv[5],geraEsfera(radius,slides,stacks));

            cout << "Ficheiro " << argv[5] << " foi criado!\n";
            return 0;

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_sphere;
            return 2;
        }

    }

    //Caixa
    if (strcmp(argv[1],"box") == 0) {

        if (argn >= 5) {

            double length = strtod(argv[2],nullptr);
            double divisions = strtod(argv[3],nullptr);
            escreverBinario(argv[4],geraCaixa(length,divisions));

            cout << "Ficheiro " << argv[4] << " foi criado!\n";
            return 0;

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_box;
            return 2;
        }

    }

    //Cone
    if (strcmp(argv[1],"cone") == 0) {

        if (argn >= 7) {

            double radius = strtod(argv[2],nullptr);
            double height = strtod(argv[3],nullptr);
            double slides = strtod(argv[4],nullptr);
            double stacks = strtod(argv[5],nullptr);
            escreverBinario(argv[6],geraCone(radius,height,slides,stacks));

            cout << "Ficheiro " << argv[6] << " foi criado!\n";
            return 0;

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_cone;
            return 2;
        }

    }

    //Plano
    if (strcmp(argv[1],"plane") == 0) {

        if (argn >= 5) {

            int length = strtod(argv[2],nullptr);
            int divisions = strtod(argv[3],nullptr);
            escreverBinario(argv[4],geraPlano(length,divisions));

            cout << "Ficheiro " << argv[4] << " foi criado!\n";
            return 0;

        }
        else {
            cerr << "Argumentos em falta";
            cerr << uso_plane;
            return 2;
        }

    }

    //Erro
    cerr << "Opção " << argv[1] <<" não disponível\n";
    cerr << "USO:\n";
    cerr << uso_sphere;
    cerr << uso_box;
    cerr << uso_cone;
    cerr << uso_plane;

    return 1;

}
