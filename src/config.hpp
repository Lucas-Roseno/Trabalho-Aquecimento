#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Files.hpp"

using namespace std;

class config
{
private:
    Files file;
    vector<vector<int>> matriz;
    int iteracao = 0;
    // Direções: cima, baixo, esquerda, direita
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<vector<bool>> jaQueimou;
    vector<pair<int, int>> fogoInicial;
    vector<pair<int, int>> apagarFogo;

public:
    void executarSimulacao();
    void imprimirMatriz();
    void propagacaoFogo();
    vector<vector<int>> espalharFogo(int posX, int posY, vector<vector<int>> novaMatriz);
    bool aindaTemFogo();
};;