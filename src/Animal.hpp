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
    vector<vector<short int>> distancias;
    vector<vector<pair<short int, short int>>> antecessores;

    short int passos;
    short int tempoParado = 0;
    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    
public:
    Animal(vector<vector<short int>>& matriz, Files& file);
    short int valorAnterior;
    pair<short int, short int> posicaoAtual;
    bool morreu = false;
    void definirPosIni(vector<vector<short int>>& matriz, Files& file);
    void rotaDeFuga(vector<vector<short int>>& matriz, Files& file);
    void reconstruirCaminho(short int destX, short int destY, vector<vector<short int>>& matriz);
    void mostrarCaminho();
};