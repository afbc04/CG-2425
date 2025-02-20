#include "engine/World.h"

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "figuras/Triangles.h"

using namespace std;

//Classe para World
World::World() {

    //Variaveis
    this->modelos_a_carregar = vector<vector<Triangle> >(); //Lista com os modelos a carregar

    //Janela
    this->height = 0;
    this->width = 0;

    //Posição
    this->pos_x = 0;
    this->pos_y = 0;
    this->pos_z = 0;

    //Vetor de visão
    this->camera_x = 0;
    this->camera_y = 0;
    this->camera_z = 0;

    //Vetor Normal
    this->normal_x = 0;
    this->normal_y = 0;
    this->normal_z = 0;

    //Projeção
    this->fov = 0;
    this->near = 0;
    this->far = 0;

    //Modo debug
    this->modo_debug = false;
    this->quantidade_max_triangulos = 0;

    // Angulos - Teste
    this->angle_x = 0;
    this->angle_y = 0;

}
