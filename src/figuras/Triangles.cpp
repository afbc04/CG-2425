#include "figuras/Triangles.h"

//Classe para Ponto
Ponto::Ponto() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Ponto::Ponto(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

//Classe para Triangulo
Triangle::Triangle() {
    this->p1 = Ponto(0,0,0);
    this->p2 = Ponto(0,0,0);
    this->p3 = Ponto(0,0,0);
}

Triangle::Triangle(Ponto p1, Ponto p2, Ponto p3) {
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}
