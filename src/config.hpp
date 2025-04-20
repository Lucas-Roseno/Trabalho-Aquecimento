#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Files.hpp"
#include "Animal.hpp"

using namespace std;

#define IteracoesMax 1000000000

class config
{
private:
    // Direções: cima, baixo, esquerda, direita
    short int dx[4] = {-1, 1, 0, 0};
    short int dy[4] = {0, 0, -1, 1};
    int iteracao = 0;
    vector<pair<int, int>> fogoInicial;

    // As direções do vento estão no .cpp. Varia de 0 a 14
    short int direcaoVento = 0;

public:
    //Variáveis
    Files file;
    vector<vector<short int>> matriz;
    Animal animal;

    //Funções
    void executarSimulacao();
    void imprimirMatriz(vector<vector<short int>> &matriz);
    void propagacaoFogo();
    vector<vector<short int>> espalharFogo(int posX, int posY, 
        vector<vector<short int>> novaMatriz);
    bool aindaTemFogo();
    short int definirDirecaoVento();
    void dispersarUmidade(short int &x, short int &y);
    void atualizarMatrizPassos();
};