#pragma once
#include <iostream>
#include <vector>
#include "Files.hpp"
using namespace std;

class Animal
{
protected:
    vector<vector<char>> matrizPassos;
    vector<vector<bool>> visitados;
    pair<short int, short int> posicaoAtual = make_pair(-1, -1);
    short int tempoParado = 0;
    // Direções: cima, baixo, esquerda, direita
    const short int dx[4] = {-1, 1, 0, 0};
    const short int dy[4] = {0, 0, -1, 1};
    short int valorAnterior;

    vector<short int> valorAdjacente;
    vector<pair<short int, short int>> posicaoAdjacente;

public:
    short int passos;
    pair<short int, short int> getPosicaoAtual();
    short int getValorAnterior();
    Animal(vector<vector<short int>> &matriz, Files &file);

    bool morreu = false;
    void rotaDeFuga(vector<vector<short int>> &matriz, Files &file);
    void reconstruirCaminho(short int destX, short int destY, vector<vector<short int>> &matriz);
    void mostrarCaminho();
    void movimentar(vector<vector<short int>> &matriz, Files &file);
    short int melhorOpcao(vector<short int> &valorAdjacente);
};