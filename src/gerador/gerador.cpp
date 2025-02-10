#include <iostream>
#include <fstream>
#include <vector>
#include "Triangles.h"

using namespace std;

// Função para desenhar um plano e armazenar os triângulos em um vetor
void desenhaPlano(int length, int divisions, vector<Triangle>& lista) {
//    lista.push_back(Triangle(1, 1, 1));  // Adicionando um triângulo de exemplo
}

void escreverBinario(const string& nomeArquivo, const vector<Triangle>& lista) {

    ofstream f(nomeArquivo, ios::binary);
    if (!f) {
        cerr << "Erro ao abrir o arquivo para escrita!" << endl;
        return;
    }

    // Escrevendo o tamanho dos vetores para facilitar a leitura posterior
    int size = lista.size();
    f.write(reinterpret_cast<const char*>(&size), sizeof(int));

    for (Triangle t : lista) {

        Ponto p1 = t.p1;

        f.write(reinterpret_cast<const char*>(&p1.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p1.y), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p1.z), sizeof(double));

        Ponto p2 = t.p2;

        f.write(reinterpret_cast<const char*>(&p2.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p2.y), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p2.z), sizeof(double));

        Ponto p3 = t.p3;

        f.write(reinterpret_cast<const char*>(&p3.x), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p3.y), sizeof(double));
        f.write(reinterpret_cast<const char*>(&p3.z), sizeof(double));
    }

    f.close();
}


// Função que recebe uma lista de triângulos
/*
void gera3D(const vector<Triangle>& lista) {
    cout << "Lista de triângulos recebida:\n";
    for (const Triangle& t : lista) {
        cout << "Triângulo: (" << t.x << ", " << t.y << ", " << t.z << ")\n";
    }
}*/

vector<Triangle> geraPlano(double size, double dimensoes) {

    vector<Triangle> lista;

    double inicio = size/2;
    double salto = size / dimensoes;

    for (int i = 0; i < dimensoes; i++) {

        for (int j = 0; j < dimensoes ; j++) {

            double ponto_inicial_x = -inicio;
            ponto_inicial_x += (i*salto);

            double ponto_inicial_z = -inicio;
            ponto_inicial_z += (j*salto);

            Ponto p1_1 = Ponto(ponto_inicial_x,0,ponto_inicial_z);
            Ponto p1_2 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z);
            Ponto p1_3 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z + salto);

            cout << "Triangulo 1\n";
            cout << "Ponto 1\n";
            cout << p1_1.x << "\n";
            cout << p1_1.y << "\n";
            cout << p1_1.z << "\n";
            cout << "Ponto 2\n";
            cout << p1_2.x << "\n";
            cout << p1_2.y << "\n";
            cout << p1_2.z << "\n";
            cout << "Ponto 3\n";
            cout << p1_3.x << "\n";
            cout << p1_3.y << "\n";
            cout << p1_3.z << "\n";

            Ponto p2_1 = Ponto(ponto_inicial_x + salto,0,ponto_inicial_z + salto);
            Ponto p2_2 = Ponto(ponto_inicial_x,0,ponto_inicial_z);
            Ponto p2_3 = Ponto(ponto_inicial_x,0,ponto_inicial_z + salto);

            cout << "Triangulo 2\n";
            cout << "Ponto 1\n";
            cout << p2_1.x << "\n";
            cout << p2_1.y << "\n";
            cout << p2_1.z << "\n";
            cout << "Ponto 2\n";
            cout << p2_2.x << "\n";
            cout << p2_2.y << "\n";
            cout << p2_2.z << "\n";
            cout << "Ponto 3\n";
            cout << p2_3.x << "\n";
            cout << p2_3.y << "\n";
            cout << p2_3.z << "\n";

            lista.push_back(Triangle(p1_1,p1_2,p1_3));
            lista.push_back(Triangle(p2_1,p2_2,p2_3));

        }

    }

    return lista;

}

int main() {
    vector<Triangle> lista = geraPlano(2,3);

    //desenhaPlano(10, 5, lista); // Preenchendo a lista de triângulos
    //gera3D(lista); // Enviando para processamento
    escreverBinario("teste.3d",lista);

    return 0;
}
