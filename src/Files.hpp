#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
class Files
{
private:
    ofstream arquivoSaida;

public:
    short int linhas, colunas, focoX, focoY;
    vector<vector<short int>> lerMatriz();
    void iniciarOutput();
    void gravarIteracao(int &iteracao, vector<vector<short int>> &matrizFogo);
    void movimentoFogo(short int x, short int y, short int valor, short int dx, short int dy);
    void fecharOutput();
    string definirDirecao(short int &dx, short int &dy);
    void dadosFinaisAnimal(vector<vector<char>> &matrizPassos, short int passos, 
        bool vida, short int iteracaoMorte, short int encontrouAgua);
};