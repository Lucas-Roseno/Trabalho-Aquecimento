#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Files.hpp"
#include "Animal.hpp"

using namespace std;

class config
{

private:
    // Direções: cima, baixo, esquerda, direita
    short int dx[4] = {-1, 1, 0, 0};
    short int dy[4] = {0, 0, -1, 1};
    int iteracao = 0;
    vector<pair<int, int>> fogoInicial;

    // Direções: sem vento = 0, acima = 1, baixo = 2, esquerda = 3, direita = 4
    // o resto está no .cpp
    short int direcaoVento = 0;

public:
    Files file;
    vector<vector<short int>> matriz;

    void executarSimulacao();
    void imprimirMatriz();
    void propagacaoFogo();
    vector<vector<short int>> espalharFogo(int posX, int posY, vector<vector<short int>> novaMatriz);
    bool aindaTemFogo();
    short int definirDirecaoVento();
    vector<vector<short int>> getMatriz() const;
    Files getFile() const;
};