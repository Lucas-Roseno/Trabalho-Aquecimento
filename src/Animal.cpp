#include "Animal.hpp"
#include <queue>
#include <algorithm>

void Animal::inicializador(vector<vector<short int>> &matriz, Files &file)
{
    visitados.resize(file.linhas, vector<bool>(file.colunas, false));
    matrizPassos.resize(file.linhas, vector<char>(file.colunas));
 
    matrizAnimal = matriz;

    for (short int i = 0; i < file.linhas; i++)
    {
        for (short int j = 0; j < file.colunas; j++)
        {
            matrizPassos[i][j] = static_cast<char>(matriz[i][j] + '0');
            if (matriz[i][j] == 0 && posicaoAtual.first == -1)
            {
                posicaoAtual = make_pair(i, j);
                matrizAnimal[i][j] = 9;
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

void Animal::movimentar(vector<vector<short int>> &matriz, Files &file, bool acessarVisitados)
{
    matrizAnimal = matriz;
    matrizAnimal[posicaoAtual.first][posicaoAtual.second] = 9;

    apagouFogo = false;

    valorAdjacente.clear();
    posicaoAdjacente.clear();

    short int posx = -1;
    short int posy = -1;

    for (size_t i = 0; i < 4; i++)
    {
        // Posição atual
        posx = posicaoAtual.first;
        posy = posicaoAtual.second;

        // olhando as casas
        posx += dx[i];
        posy += dy[i];

        // guarda os valores e posições
        if (posx >= 0 && posx < file.linhas && posy >= 0 && posy < file.colunas)
        {
            valorAdjacente.push_back(matrizAnimal[posx][posy]);
            posicaoAdjacente.push_back(pair(posx, posy));
        }
    }

    valorI = melhorOpcao(valorAdjacente, posicaoAdjacente, visitados, acessarVisitados);

    if (valorI != -1)
    {
        posx = posicaoAdjacente[valorI].first;
        posy = posicaoAdjacente[valorI].second;

        // matrizes
        matrizAnimal[posicaoAtual.first][posicaoAtual.second] = valorAnterior;
        matrizAnimal[posx][posy] = 9;

        visitados[posicaoAtual.first][posicaoAtual.second] = true;

        matrizPassos[posicaoAtual.first][posicaoAtual.second] = '*';
        matrizPassos[posx][posy] = '9';

        passos++;
        tempoParado = 0;

        valorAnterior = valorAdjacente[valorI];
        if (valorAnterior == 4)
        {   
            dispersarUmidade(posx, posy, matrizAnimal, file);
            apagouFogo = true;
        }

        posicaoAtual = pair(posx, posy);
    }
    else
    {
        tempoParado++;
    }
}

short int Animal::melhorOpcao(vector<short int> &valorAdjacente,
                              vector<pair<short int, short int>> &posicaoAdjacente, vector<vector<bool>> &visitados,
                              bool acessarVisitados)
{
    short int posicao1ou0 = -1;
    short int posicao3 = -1;

    for (size_t i = 0; i < valorAdjacente.size(); i++)
    {
        short int x = posicaoAdjacente[i].first;
        short int y = posicaoAdjacente[i].second;

        if (valorAdjacente[i] == 4)
        {
            return i;
        }
        else if ((valorAdjacente[i] == 1 || valorAdjacente[i] == 0) &&
                 (acessarVisitados || !visitados[x][y]) && posicao1ou0 == -1)
        {
            posicao1ou0 = i;
        }
        else if (valorAdjacente[i] == 3 &&
                 (acessarVisitados || !visitados[x][y]) && posicao3 == -1)
        {
            posicao3 = i;
        }
    }

    if (posicao1ou0 != -1)
    {
        return posicao1ou0;
    }
    if (posicao3 != -1)
    {
        return posicao3;
    }
    return -1;
}

void Animal::dispersarUmidade(short int &x, short int &y, vector<vector<short int>> &matriz,
                              Files &file)
{
    valorAnterior = 0;
    for (size_t i = 0; i < 4; i++)
    {
        short int posx = x + dx[i];
        short int posy = y + dy[i];

        if (posx >= 0 && posx < file.linhas && posy >= 0 && posy < file.colunas)
        {
            if (matriz[posx][posy] != 4)
            {
                matriz[posx][posy] = 1;
            }
        }
    }
}