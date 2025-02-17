
#include "engine/World.h"
#include "tinyxml/tinyxml.h"
#include "ficheiro3d/Ficheiro.h"

void processaXML_janela(FILE* f,World& w,TiXmlElement* janela) {

    //Janela não existe
    if (janela == nullptr) {
        fprintf(f,"[JANELA] Não existe...\n");
        return;
    }

    //Obter width
    const char* width = janela->Attribute("width");

        //Width não existe
        if (width == nullptr) {
            fprintf(f,"[JANELA::width] Não existe\n");
        }
        else {
            w.width = atoi(width);
            fprintf(f,"[JANELA::width] Definido!\n");
        }


    //Obter height
    const char* height = janela->Attribute("height");

        //Height não existe
        if (height == nullptr) {
            fprintf(f,"[JANELA::height] Não existe\n");
        }
        else {
            w.height = atoi(height);
            fprintf(f,"[JANELA::height] Definido!\n");
        }

}

void processaXML_camera(FILE* f,World& w,TiXmlElement* camera) {

    //Camera não existe
    if (camera == nullptr) {
        fprintf(f,"[CAMERA] Não existe...\n");
        return;
    }

    //Obter position
    TiXmlElement* position = camera->FirstChildElement("position");

        //Verifica se posição existe
        if (position != nullptr) {

            //Obter posição x
            const char* position_x = position->Attribute("x");

            //Posição x não existe
            if (position_x == nullptr) {
                fprintf(f,"[CAMERA::position::x] Não existe\n");
            }
            else {
                w.pos_x = atoi(position_x);
                fprintf(f,"[CAMERA::position::x] Definido!\n");
            }

            //Obter posição y
            const char* position_y = position->Attribute("y");

            //Posição y não existe
            if (position_y == nullptr) {
                fprintf(f,"[CAMERA::position::y] Não existe\n");
            }
            else {
                w.pos_y = atoi(position_y);
                fprintf(f,"[CAMERA::position::y] Definido!\n");
            }

            //Obter posição z
            const char* position_z = position->Attribute("z");

            //Posição z não existe
            if (position_z == nullptr) {
                fprintf(f,"[CAMERA::position::z] Não existe\n");
            }
            else {
                w.pos_z = atoi(position_z);
                fprintf(f,"[CAMERA::position::z] Definido!\n");
            }

        }
        //Posição não existe
        else {
            fprintf(f,"[CAMERA::position] Não existe...\n");
        }

    //Obter lookAt
    TiXmlElement* lookAt = camera->FirstChildElement("lookAt");

        //Verifica se lookAt existe
        if (lookAt != nullptr) {

            //Obter camera x
            const char* camera_x = lookAt->Attribute("x");

            //camera x não existe
            if (camera_x == nullptr) {
                fprintf(f,"[CAMERA::lookAt::x] Não existe\n");
            }
            else {
                w.camera_x = atoi(camera_x);
                fprintf(f,"[CAMERA::lookAt::x] Definido!\n");
            }

            //Obter camera y
            const char* camera_y = lookAt->Attribute("y");

            //camera y não existe
            if (camera_y == nullptr) {
                fprintf(f,"[CAMERA::lookAt::y] Não existe\n");
            }
            else {
                w.camera_y = atoi(camera_y);
                fprintf(f,"[CAMERA::lookAt::y] Definido!\n");
            }

            //Obter camera z
            const char* camera_z = lookAt->Attribute("z");

            //camera z não existe
            if (camera_z == nullptr) {
                fprintf(f,"[CAMERA::lookAt::z] Não existe\n");
            }
            else {
                w.camera_z = atoi(camera_z);
                fprintf(f,"[CAMERA::lookAt::z] Definido!\n");
            }

        }
        //lookAt não existe
        else {
            fprintf(f,"[CAMERA::lookAt] Não existe...\n");
        }

    //Obter up
    TiXmlElement* up = camera->FirstChildElement("up");

        //Verifica se vetor normal existe
        if (up != nullptr) {

            //Obter vetor normal x
            const char* up_x = up->Attribute("x");

            //Vetor normal x não existe
            if (up_x == nullptr) {
                fprintf(f,"[CAMERA::up::x] Não existe\n");
            }
            else {
                w.normal_x = atoi(up_x);
                fprintf(f,"[CAMERA::up::x] Definido!\n");
            }

            //Obter vetor normal y
            const char* up_y = up->Attribute("y");

            //Vetor normal y não existe
            if (up_y == nullptr) {
                fprintf(f,"[CAMERA::up::y] Não existe\n");
            }
            else {
                w.normal_y = atoi(up_y);
                fprintf(f,"[CAMERA::up::y] Definido!\n");
            }

            //Obter vetor normal z
            const char* up_z = up->Attribute("z");

            //Vetor normal z não existe
            if (up_z == nullptr) {
                fprintf(f,"[CAMERA::up::z] Não existe\n");
            }
            else {
                w.normal_z = atoi(up_z);
                fprintf(f,"[CAMERA::up::z] Definido!\n");
            }

        }
        //Vetor normal não existe
        else {
            fprintf(f,"[CAMERA::up] Não existe...\n");
        }

    //Obter projection
    TiXmlElement* projection = camera->FirstChildElement("projection");

        //Verifica se projeção existe
        if (projection != nullptr) {

            //Obter fov
            const char* fov = projection->Attribute("fov");

            //Fov não existe
            if (fov == nullptr) {
                fprintf(f,"[CAMERA::projection::fov] Não existe\n");
            }
            else {
                w.fov = atoi(fov);
                fprintf(f,"[CAMERA::projection::fov] Definido!\n");
            }

            //Obter near
            const char* near = projection->Attribute("near");

            //Near não existe
            if (near == nullptr) {
                fprintf(f,"[CAMERA::projection::near] Não existe\n");
            }
            else {
                w.near = atoi(near);
                fprintf(f,"[CAMERA::projection::near] Definido!\n");
            }

            //Obter far
            const char* far = projection->Attribute("far");

            //Far não existe
            if (far == nullptr) {
                fprintf(f,"[CAMERA::projection::far] Não existe\n");
            }
            else {
                w.far = atoi(far);
                fprintf(f,"[CAMERA::projection::far] Definido!\n");
            }

        }
        //Projeção não existe
        else {
            fprintf(f,"[CAMERA::projection] Não existe...\n");
        }

}

void processaXML_model(FILE* f,World& w,TiXmlElement* models) {

    //Models não existe
    if (models == nullptr) {
        fprintf(f,"[GRUPOS::models] Não existe...\n");
        return;
    }

    //Obter model
    TiXmlElement* model = models->FirstChildElement("model");

    //Enquanto há model, continua
    while (model) {

        //Verifica se model existe
        if (model != nullptr) {

            //Obter pathname
            const char* pathname = model->Attribute("file");

            //pathname não existe
            if (pathname == nullptr) {
                fprintf(f,"[GRUPO::models::model::file] Não existe\n");
            }
            else {
                vector<Triangle> novo_modelo_carregado = lerBinario(pathname);
                w.modelos_a_carregar.push_back(novo_modelo_carregado);
                fprintf(f,"[GRUPO::models::model::file] Adicionado modelo %s!\n",pathname);
            }

        }
        //Model não existe
        else {
            fprintf(f,"[GRUPO::models::model] Não existe...\n");
        }

        //Coletar o outro model
        model = model->NextSiblingElement("model");

    }

}

void processaXML_grupo(FILE* f,World& w,TiXmlElement* grupo) {

    //Grupo não existe
    if (grupo == nullptr) {
        fprintf(f,"[GRUPOS] Não existe...\n");
        return;
    }

    //Obter models
    TiXmlElement* models = grupo->FirstChildElement("models");
    processaXML_model(f,w,models);

}

bool processaXML(World& w,TiXmlDocument xml) {

    //Extrair o "world"
    TiXmlElement* world = xml.FirstChildElement("world");

    //Criar ficheiro de log
    FILE* logger = fopen("xml_logger.txt","w");

    //Verifica se a criação do ficheiro aconteceu com sucesso
    if (logger == nullptr) {
        std::cerr << "Criação de ficheiro de logger de xml falhou\n";
        return false;
    }

    //World não existe
    if (world == nullptr) {
        std::cerr << "Erro: <world> não existe\n";
        return false;
    }
    
    //Processa Janela
    processaXML_janela(logger,w,world->FirstChildElement("window"));

    //Processa Camera
    processaXML_camera(logger,w,world->FirstChildElement("camera"));

    //Processa Grupo
    processaXML_grupo(logger,w,world->FirstChildElement("group"));

    fclose(logger);

    return true;

}