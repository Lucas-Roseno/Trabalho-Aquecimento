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
    valorAdjacente.clear();
    posicaoAdjacente.clear();

    for (short int i = 0; i < 4; i++)
    {
        short int posx = posicaoAtual.first;
        short int posy = posicaoAtual.second;
        posx += dx[i];
        posy += dy[i];

        if (posx >= 0 && posx < file.linhas &&
            posy >= 0 && posy < file.colunas &&
            matriz[posx][posy] == 4)
        {
            passos++;
            matriz[posicaoAtual.first][posicaoAtual.second] = valorAnterior;
            visitados[posicaoAtual.first][posicaoAtual.second] = true;
            matrizPassos[posicaoAtual.first][posicaoAtual.second] = '*';

            // Atualiza o valor anterior antes de modificar a matriz
            valorAnterior = matriz[posx][posy];

            posicaoAtual.first = posx;
            posicaoAtual.second = posy;
            matriz[posx][posy] = 9;
            matrizPassos[posx][posy] = '9';

            for (short int j = 0; j < 4; j++)
            {
                if ((posx + dx[j]) >= 0 && (posx + dx[j]) < file.linhas &&
                    (posy + dy[j]) >= 0 && (posy + dy[j]) < file.colunas)
                {
                    matriz[posx + dx[j]][posy + dy[j]] = 1;
                }
            }
            return;
        }
        else if (posx >= 0 && posx < file.linhas &&
                 posy >= 0 && posy < file.colunas)
        {
            valorAdjacente.push_back(matriz[posx][posy]);
            posicaoAdjacente.push_back(make_pair(posx, posy));
        }
    }

    short int posicaoI = melhorOpcao(valorAdjacente);
    if (posicaoI != -1)
    {
        pair<short int, short int> posAux = posicaoAdjacente[posicaoI];

        // Atualiza o valor anterior antes de modificar a matriz
        valorAnterior = matriz[posAux.first][posAux.second];

        matriz[posicaoAtual.first][posicaoAtual.second] = valorAnterior;
        matrizPassos[posicaoAtual.first][posicaoAtual.second] = '*';
        matriz[posAux.first][posAux.second] = 9;
        matrizPassos[posAux.first][posAux.second] = '9';
        visitados[posicaoAtual.first][posicaoAtual.second] = true;
        posicaoAtual = posAux;

        passos++;
    }
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