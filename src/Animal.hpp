#pragma once
#include <iostream>
#include <vector>
#include "Files.hpp"
using namespace std;

class Animal
{
protected:
    vector<vector<bool>> visitados;

    // Direções: cima, baixo, esquerda, direita
    const short int dx[4] = {-1, 1, 0, 0};
    const short int dy[4] = {0, 0, -1, 1};

    vector<short int> valorAdjacente;
    vector<pair<short int, short int>> posicaoAdjacente;

public:
    Animal() = default;
    void inicializador(vector<vector<short int>> &matriz, Files &file);

    //variáveis
    vector<vector<short int>> matrizAnimal;
    vector<vector<char>> matrizPassos;
    pair<short int, short int> posicaoAtual = make_pair(-1, -1);
    short int iteracaoMorte = -1;
    short int tempoParado = 0;
    short int valorAnterior = 0;
    short int passos = 0;
    bool morreu = false;
    short int valorI = -1;
    bool apagouFogo = false;
    short int encontrouAgua = 0;

    //funções
    void rotaDeFuga(vector<vector<short int>> &matriz, Files &file);
    void reconstruirCaminho(short int destX, short int destY, vector<vector<short int>> &matriz);
    void movimentar(vector<vector<short int>> &matriz, Files &file, bool acessarVisitados);

    short int melhorOpcao(vector<short int> &valorAdjacente,
                          vector<pair<short int, short int>> &posicaoAdjacente,
                          vector<vector<bool>> &visitados, bool acessarVisitados);

    void dispersarUmidade(short int &x, short int &y, vector<vector<short int>> &matriz, Files &file);
};