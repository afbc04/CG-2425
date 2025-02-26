#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"
#include <math.h>

using namespace std;

vector<Triangle> geraEsfera(double radius, double slices, double stacks) {

    vector<Triangle> lista;

    for (int i = 0; i < stacks; ++i) {

        float alpha1 = M_PI * i / stacks;
        float alpha2 = M_PI * (i + 1) / stacks;

        for (int j = 0; j < slices; ++j) {
            float beta1 = -2.0f * M_PI * j / slices;
            float beta2 = -2.0f * M_PI * (j + 1) / slices;

            float x1 = radius * sin(alpha1) * sin(beta1);
            float y1 = radius * cos(alpha1);
            float z1 = radius * sin(alpha1) * cos(beta1);

            float x2 = radius * sin(alpha2) * sin(beta1);
            float y2 = radius * cos(alpha2);
            float z2 = radius * sin(alpha2) * cos(beta1);

            float x3 = radius * sin(alpha1) * sin(beta2);
            float y3 = radius * cos(alpha1);
            float z3 = radius * sin(alpha1) * cos(beta2);

            float x4 = radius * sin(alpha2) * sin(beta2);
            float y4 = radius * cos(alpha2);
            float z4 = radius * sin(alpha2) * cos(beta2);

            Ponto p1 = Ponto(x1,y1,z1);
            Ponto p2 = Ponto(x2,y2,z2);
            Ponto p3 = Ponto(x3,y3,z3);
            Ponto p4 = Ponto(x4,y4,z4);

            lista.push_back(Triangle(p2,p1,p3));
            lista.push_back(Triangle(p2,p3,p4));
        }
    }

    return lista;

}
vector<Triangle> geraCaixa(double length, double divisions) {
    if (divisions <= 0) {
        throw invalid_argument("divisions must be greater than zero");
    }

    vector<Triangle> lista;
    double step = length / divisions;
    double half = length / 2.0;

    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            double x1 = -half + i * step;
            double x2 = x1 + step;
            double y1 = -half + j * step;
            double y2 = y1 + step;

            // Face inferior (-Y) (corrigida)
            lista.push_back(Triangle(Ponto(x1, -half, y1), Ponto(x2, -half, y1), Ponto(x1, -half, y2)));
            lista.push_back(Triangle(Ponto(x2, -half, y1), Ponto(x2, -half, y2), Ponto(x1, -half, y2)));

            // Face superior (+Y) (corrigida)
            lista.push_back(Triangle(Ponto(x1, half, y1), Ponto(x1, half, y2), Ponto(x2, half, y1)));
            lista.push_back(Triangle(Ponto(x2, half, y1), Ponto(x1, half, y2), Ponto(x2, half, y2)));

            // Face frontal (+Z) (corrigida)
            lista.push_back(Triangle(Ponto(x1, y1, half), Ponto(x2, y1, half), Ponto(x1, y2, half)));
            lista.push_back(Triangle(Ponto(x2, y1, half), Ponto(x2, y2, half), Ponto(x1, y2, half)));

            // Face traseira (-Z) (corrigida)
            lista.push_back(Triangle(Ponto(x1, y1, -half), Ponto(x1, y2, -half), Ponto(x2, y1, -half)));
            lista.push_back(Triangle(Ponto(x2, y1, -half), Ponto(x1, y2, -half), Ponto(x2, y2, -half)));

            // Face esquerda (-X) (corrigida)
            lista.push_back(Triangle(Ponto(-half, y1, x1), Ponto(-half, y1, x2), Ponto(-half, y2, x1)));
            lista.push_back(Triangle(Ponto(-half, y2, x1), Ponto(-half, y1, x2), Ponto(-half, y2, x2)));

            // Face direita (+X) (corrigida)
            lista.push_back(Triangle(Ponto(half, y1, x1), Ponto(half, y2, x1), Ponto(half, y1, x2)));
            lista.push_back(Triangle(Ponto(half, y2, x1), Ponto(half, y2, x2), Ponto(half, y1, x2)));
        }
    }

    return lista;
}

vector<Triangle> geraCone(double radius, double height, int slices, int stacks) {
    vector<Triangle> lista;

    //Base do cone
    for (int i = 0; i < slices; i++) {

        double alfa1 = ((2.0f * M_PI)/slices) * i;
        double alfa2 = ((2.0f * M_PI)/slices) * (i+1);

        Ponto origem = Ponto(0,0,0);
        Ponto p1 = Ponto(radius*sin(alfa1),0,radius*cos(alfa1));
        Ponto p2 = Ponto(radius*sin(alfa2),0,radius*cos(alfa2));

        lista.push_back(Triangle(origem,p2,p1));
    }

    //Corpo do cone
    double delta_h = height/stacks;
    double h = 0;
    for (int i = 0; i < stacks; i++) {

        double h2 = h + delta_h; //Altura da circunferência de cima
        double raio1 = radius * ((height - h) / height); //Raio da circunferencia de baixo
        double raio2 = radius * ((height - h2) / height); //Raio da circunferencia de cima

        for (int j = 0; j < slices; j++) {

            double alfa1 = (2.0f * M_PI)/slices * j;
            double alfa2 = (2.0f * M_PI)/slices * (j+1);

            Ponto p1 = Ponto(raio2*sin(alfa1),h2,raio2*cos(alfa1));
            Ponto p2 = Ponto(raio2*sin(alfa2),h2,raio2*cos(alfa2));
            Ponto p3 = Ponto(raio1*sin(alfa1),h,raio1*cos(alfa1));
            Ponto p4 = Ponto(raio1*sin(alfa2),h,raio1*cos(alfa2));

            lista.push_back(Triangle(p3, p4, p1));
            lista.push_back(Triangle(p1, p4, p2));
        }

        h += delta_h;
    }

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
            
            //Gerar esfera - sucesso
            if (escreverBinario(argv[5],geraEsfera(radius,slides,stacks))) {

                cout << "Ficheiro " << argv[5] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[5] << "!\n";
                return 1;

            }

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

            //Gerar Caixa - sucesso
            if (escreverBinario(argv[4],geraCaixa(length,divisions))) {

                cout << "Ficheiro " << argv[4] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[4] << "!\n";
                return 1;

            }

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

            //Gerar Cone - sucesso
            if (escreverBinario(argv[6],geraCone(radius,height,slides,stacks))) {

                cout << "Ficheiro " << argv[6] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[6] << "!\n";
                return 1;

            }

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

            //Gerar plano - sucesso
            if (escreverBinario(argv[4],geraPlano(length,divisions))) {

                cout << "Ficheiro " << argv[4] << " foi criado!\n";
                return 0;

            }
            else {

                cerr << "Não foi possivel criar o " << argv[4] << "!\n";
                return 1;

            }

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