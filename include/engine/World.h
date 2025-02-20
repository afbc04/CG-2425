#ifndef WORLD_ENGINE_HEADER
#define WORLD_ENGINE_HEADER

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"

using namespace std;

    // Classe para World
    class World {
        public:
            
            vector<vector<Triangle> > modelos_a_carregar; //Lista com os modelos a carregar

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

            // Angulos - Teste
            double angle_x = 0;
            double angle_y = 0;
            double angle_z = 0;

            World();
    };

#endif