#include "Animal.hpp"
#include <queue>
#include <algorithm>

Animal::Animal(vector<vector<short int>>& matriz, Files& file)
{
    visitados.resize(file.linhas, vector<bool>(file.colunas, false));
    distancias.resize(file.linhas, vector<short int>(file.colunas, -1));
    matrizPassos.resize(file.linhas, vector<char>(file.colunas));
    for (short int i = 0; i < file.linhas; i++)
    {
        for (short int j = 0; j < file.colunas; j++)
        {
            matrizPassos[i][j] = static_cast<char>(matriz[i][j] + '0');
        }
    }
}

void Animal::definirPosIni(vector<vector<short int>>& matriz, Files& file)
{
    for (short int i = 0; i < file.linhas; i++)
    {
        for (short int j = 0; j < file.colunas; j++)
        {
            if (matriz[i][j] == 0)
            {
                valorAnterior = matriz[i][j];
                matriz[i][j] = 9;
                posicaoAtual = make_pair(i, j);
                return;
            }
        }
    }
}

void Animal::rotaDeFuga(vector<vector<short int>>& matriz, Files& file)
{
    antecessores.clear();
    antecessores.resize(file.linhas, vector<pair<short int, short int>>(file.colunas, {-1, -1}));

    queue<pair<short int, short int>> fila;
    fila.push(posicaoAtual);

    visitados[posicaoAtual.first][posicaoAtual.second] = true;
    distancias[posicaoAtual.first][posicaoAtual.second] = 0;

    short int posX, posY;
    while (!fila.empty())
    {
        pair<short int, short int> posicaoAux = fila.front();
        fila.pop();

        for (int i = 0; i < 4; i++)
        {
            posX = posicaoAux.first + dx[i];
            posY = posicaoAux.second + dy[i];

    
            if (posX < 0 || posY < 0 || posX >= file.linhas || posY >= file.colunas)
            {
                continue;
            }else if (matriz[posX][posY] == 2)
            {
                continue;
            }else if(visitados[posX][posY]){
                continue;
            }

            visitados[posX][posY] = true;
            distancias[posX][posY] = distancias[posicaoAux.first][posicaoAux.second] + 1; 
            antecessores[posX][posY] = posicaoAux;

            if (matriz[posX][posY] == 0)
            {
                /* code */
            }
            

            fila.push({posX, posY});


        }   
    }
}

void Animal::reconstruirCaminho(short int destX, short int destY, vector<vector<short int>>& matriz){
    vector<pair<short int, short int>> caminho;
    int x = destX;
    int y = destY;

    while (x != -1 && y != -1)
    {
        caminho.push_back({x, y});
        auto [prevX, prevY] = antecessores[x][y];
        x = prevX;
        y = prevY;   
    }

    passos += caminho.size() - 1;
    reverse(caminho.begin(), caminho.end());

    for(size_t i = 0; i < caminho.size(); i++){
        pair<short int, short int> posicao = caminho[i];
        matriz[posicao.first][posicao.second] = '*';        

    }

    mostrarCaminho();
    


}

void Animal::mostrarCaminho(){
    for (const auto& linha : matrizPassos)
    {
      for (const auto& elemento : linha)
      {
        cout << elemento << " ";
      }
      cout << "\n";
    }
    cout << "\n";
}