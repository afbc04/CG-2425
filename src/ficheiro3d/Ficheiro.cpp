#include <iostream>
#include <fstream>
#include <vector>
#include "figuras/Triangles.h"
#include "ficheiro3d/Ficheiro.h"

using namespace std;

//Escrever uma figura em ficheiro texto
bool escreverBinario(const string nome_ficheiro, const vector<Triangle>& lista) {

    ofstream f (nome_ficheiro, ios::binary);

    //Verifica se correu tudo bem
    if (!f) {
        cerr << "Erro ao criar o ficheiro " << nome_ficheiro << endl;
        return false;
    }

    //Escrever a quantidade de triangulos
    int size = lista.size();
    f.write(reinterpret_cast<const char*>(&size), sizeof(int));

    //Escrever cada ponto
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
    return true;
}

//Ler Ficheiros .3d
vector<Triangle> lerBinario(const string nome_ficheiro) {

    ifstream f(nome_ficheiro, ios::binary);

    //Verifica se correu tudo bem
    if (!f) {
        cerr << "Erro ao abrir o arquivo " << nome_ficheiro << endl;
        return vector<Triangle>();
    }

    vector<Triangle> lista;

    //Ler quantidade de triangulos a ler
    int tamanho;
    f.read(reinterpret_cast<char*>(&tamanho), sizeof(int));

    //Ler os triangulos
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

    return lista;
}

//Ficheiro .3d para texto
int ficheiroParaTexto(const string nome_ficheiro, const string output) {

    ifstream f(nome_ficheiro, ios::binary);
    ofstream out(output, ios::binary);

    //Verifica se correu tudo bem
    if (!f || !out) {
        return 0;
    }

    //Ler quantidade de triangulos a ler
    int tamanho;
    f.read(reinterpret_cast<char*>(&tamanho), sizeof(int));
    out << tamanho << "\n\n";

    //Ler os triangulos
    for (int i = 0; i < tamanho; i++) {

        double x1, y1, z1;
        f.read(reinterpret_cast<char*>(&x1), sizeof(double));
        f.read(reinterpret_cast<char*>(&y1), sizeof(double));
        f.read(reinterpret_cast<char*>(&z1), sizeof(double));
        out << x1 << " ";
        out << y1 << " ";
        out << z1 << "\n";

		double x2, y2, z2;
        f.read(reinterpret_cast<char*>(&x2), sizeof(double));
        f.read(reinterpret_cast<char*>(&y2), sizeof(double));
        f.read(reinterpret_cast<char*>(&z2), sizeof(double));
        out << x2 << " ";
        out << y2 << " ";
        out << z2 << "\n";

		double x3, y3, z3;
        f.read(reinterpret_cast<char*>(&x3), sizeof(double));
        f.read(reinterpret_cast<char*>(&y3), sizeof(double));
        f.read(reinterpret_cast<char*>(&z3), sizeof(double));
        out << x3 << " ";
        out << y3 << " ";
        out << z3 << "\n\n";

    }

    f.close();
    out.close();

    return 1;
}