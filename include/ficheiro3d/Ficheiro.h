#ifndef FICHEIRO_HEADER
#define FICHEIRO_HEADER

#include <vector>
#include <string>
#include "figuras/Triangles.h"

using namespace std;

bool escreverBinario(const string nome_ficheiro, const vector<Triangle>& lista);
vector<Triangle> lerBinario(const string nome_ficheiro);

#endif