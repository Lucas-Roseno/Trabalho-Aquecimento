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
#define IMPRIMIR_COM_EMOJI 1 //1 imprime emojis; 0 para imprimir os números normais

class config
{
private:
    // Direções: cima, baixo, esquerda, direita
    short int dx[4] = {-1, 1, 0, 0};
    short int dy[4] = {0, 0, -1, 1};
    int iteracao = 0;
    vector<pair<int, int>> fogoInicial;

    // Possíveis direções de vento (cada entrada é um conjunto de vetores cardeais)
    vector<vector<pair<short int, short int>>> direcoesVento = {
        {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, // 0: sem vento
        {{-1, 0}},                          // 1: cima
        {{1, 0}},                           // 2: baixo
        {{0, -1}},                          // 3: esquerda
        {{0, 1}},                           // 4: direita
        {{-1, 0}, {0, -1}},                 // 5: cima e esquerda  (antes era {-1,-1})
        {{-1, 0}, {0, 1}},                  // 6: cima e direita  (antes era {-1, 1})
        {{1, 0}, {0, -1}},                  // 7: baixo e esquerda(atualiza de {1,-1})
        {{1, 0}, {0, 1}},                   // 8: baixo e direita(atualiza de {1, 1})
        {{-1, 0}, {0, -1}, {0, 1}},         // 9: cima, esquerda e direita
        {{-1, 0}, {1, 0}, {0, -1}},         // 10: cima, baixo e esquerda
        {{-1, 0}, {1, 0}, {0, 1}},          // 11: cima, baixo e direita
        {{1, 0}, {0, -1}, {0, 1}},          // 12: baixo, esquerda e direita
        {{0, -1}, {0, 1}},                  // 13: esquerda e direita
        {{-1, 0}, {1, 0}}                   // 14: cima e baixo
    };
    // Direção que será usada na simulação
    short int direcaoVento = 0;

public:
    // Variáveis
    Files file;
    vector<vector<short int>> matriz;
    Animal animal;

    // Funções
    void executarSimulacao();
    template <typename T>
    void imprimirMatriz(vector<vector<T>> &matriz);
    void propagacaoFogo();
    vector<vector<short int>> espalharFogo(int posX, int posY,
                                           vector<vector<short int>> novaMatriz);
    bool aindaTemFogo();
    void atualizarMatrizPassos();
};