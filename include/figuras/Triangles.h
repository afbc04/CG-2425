#ifndef TRIANGLES_HEADER
#define TRIANGLES_HEADER

    // Classe para Ponto
    class Ponto {
        public:
            double x, y, z;

            Ponto();
            Ponto(double x, double y, double z);
    };

    // Classe para Triangulo
    class Triangle {
        public:
            Ponto p1, p2, p3;

            Triangle();
            Triangle(Ponto p1, Ponto p2, Ponto p3);
            
    };


#endif
