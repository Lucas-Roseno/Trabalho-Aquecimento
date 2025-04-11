#include "Animal.hpp"
#include <queue>
#include <algorithm>

Animal::Animal(vector<vector<short int>> &matriz, Files &file)
{
    passos = 0;
    visitados.resize(file.linhas, vector<bool>(file.colunas, false));
    matrizPassos.resize(file.linhas, vector<char>(file.colunas));
    for (short int i = 0; i < file.linhas; i++)
    {
        for (short int j = 0; j < file.colunas; j++)
        {
            matrizPassos[i][j] = static_cast<char>(matriz[i][j] + '0');
            valorAnterior = matriz[i][j];
            if (matriz[i][j] == 0 && posicaoAtual.first == -1)
            {
                cout << "Valor anterior: " << valorAnterior << endl;
                cout << "Posição atual: " << posicaoAtual.first << "," << posicaoAtual.second << endl;
                valorAnterior = matriz[i][j];
                posicaoAtual = make_pair(i, j);
                cout << "Posição atual: " << posicaoAtual.first << "," << posicaoAtual.second << endl;
                matriz[i][j] = 9;
                matrizPassos[i][j] = '9';
                visitados[i][j] = true;
            }
        }
    }
}

pair<short int, short int> Animal::getPosicaoAtual()
{
    return posicaoAtual;
}

short int Animal::getValorAnterior()
{
    return valorAnterior;
}

void Animal::mostrarCaminho()
{
    for (const auto &linha : matrizPassos)
    {
        for (const auto &elemento : linha)
        {
            cout << elemento << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void Animal::movimentar(vector<vector<short int>> &matriz, Files &file)
{

}

short int Animal::melhorOpcao(vector<short int> &valorAdjacente)
{
    short int posicao3;
    bool achou3;
    for (size_t i = 0; i < valorAdjacente.size(); i++)
    {
        if ((valorAdjacente[i] == 1 || valorAdjacente[i] == 0))
        {
            return i;
        }
        else if (valorAdjacente[i] == 3)
        {
            achou3 = true;
            posicao3 = i;
        }
    }

    if (achou3)
    {
        return posicao3;
    }
    else
    {
        return -1;
    }
}