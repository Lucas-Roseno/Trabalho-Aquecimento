#include "config.hpp"

void config::executarSimulacao()
{
  matriz = file.lerMatriz();
  matriz[file.focoX][file.focoY] = 2;

  cout << "\nMatriz de entrada:" << endl;
  imprimirMatriz();

  while (aindaTemFogo() && iteracao < 7)

  {
    jaQueimou = vector<vector<bool>>(file.linhas, vector<bool>(file.colunas, false));

    for (const auto &fogo : fogoInicial)
    {
      matriz[fogo.first][fogo.second] = 3;
    }

    propagacaoFogo();

    cout << "Iteracao " << iteracao << ":" << endl;
    imprimirMatriz();

    iteracao++;
  }
}

void config::imprimirMatriz()
{
  for (int i = 0; i < file.linhas; i++)
  {
    for (int j = 0; j < file.colunas; j++)
    {
      cout << matriz[i][j] << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

void config::propagacaoFogo()
{
  fogoInicial.clear();
  vector<vector<int>> novaMatriz = matriz;

  for (int i = 0; i < file.linhas; i++)
  {
    for (int j = 0; j < file.colunas; j++)
    {
      if (matriz[i][j] == 2)
      {
        novaMatriz = espalharFogo(i, j, novaMatriz);
        fogoInicial.push_back(make_pair(i, j));
      }
    }
  }
  matriz = novaMatriz;
}

vector<vector<int>> config::espalharFogo(int posX, int posY, vector<vector<int>> novaMatriz)
{
  switch (direcaoVento)
  {
  case 0: // Sem vento
    for (int i = 0; i < 4; i++)
    {
      if (posX + dx[i] >= 0 && posX + dx[i] < file.linhas &&
          posY + dy[i] >= 0 && posY + dy[i] < file.colunas &&
          novaMatriz[posX + dx[i]][posY + dy[i]] == 1)
      {
        novaMatriz[posX + dx[i]][posY + dy[i]] = 2;
      }
    }
    break;
  case 1: // cima
    if (posX - 1 >= 0 && novaMatriz[posX - 1][posY] == 1)
    {
      novaMatriz[posX - 1][posY] = 2;
    }
    break;
  case 2: // baixo
    if (posX + 1 < file.linhas && novaMatriz[posX + 1][posY] == 1)
    {
      novaMatriz[posX + 1][posY] = 2;
    }
    break;
  case 3: // esquerda
    if (posY - 1 >= 0 && novaMatriz[posX][posY - 1] == 1)
    {
      novaMatriz[posX][posY - 1] = 2;
    }
    break;
  case 4: // direita
    if (posY + 1 < file.colunas && novaMatriz[posX][posY + 1] == 1)
    {
      novaMatriz[posX][posY + 1] = 2;
    }
    break;
  case 5: // cima e esquerda
    if (posX - 1 >= 0 && posY - 1 >= 0 && novaMatriz[posX - 1][posY - 1] == 1)
    {
      novaMatriz[posX - 1][posY - 1] = 2;
    }
    break;
  case 6: // cima e direita
    if (posX - 1 >= 0 && posY + 1 < file.colunas && novaMatriz[posX - 1][posY + 1] == 1)
    {
      novaMatriz[posX - 1][posY + 1] = 2;
    }
    break;
  case 7: // baixo e esquerda
    if (posX + 1 < file.linhas && posY - 1 >= 0 && novaMatriz[posX + 1][posY - 1] == 1)
    {
      novaMatriz[posX + 1][posY - 1] = 2;
    }
    break;
  case 8: // baixo e direita
    if (posX + 1 < file.linhas && posY + 1 < file.colunas && novaMatriz[posX + 1][posY + 1] == 1)
    {
      novaMatriz[posX + 1][posY + 1] = 2;
    }
    break;
  case 9: // cima, esquerda e direita
    if (posX - 1 >= 0 && novaMatriz[posX - 1][posY] == 1)
    {
      novaMatriz[posX - 1][posY] = 2;
    }
    if (posY - 1 >= 0 && novaMatriz[posX][posY - 1] == 1)
    {
      novaMatriz[posX][posY - 1] = 2;
    }
    if (posY + 1 < file.colunas && novaMatriz[posX][posY + 1] == 1)
    {
      novaMatriz[posX][posY + 1] = 2;
    }
    break;
  case 10: // cima, baixo e esquerda
    if (posX - 1 >= 0 && novaMatriz[posX - 1][posY] == 1)
    {
      novaMatriz[posX - 1][posY] = 2;
    }
    if (posX + 1 < file.linhas && novaMatriz[posX + 1][posY] == 1)
    {
      novaMatriz[posX + 1][posY] = 2;
    }
    if (posY - 1 >= 0 && novaMatriz[posX][posY - 1] == 1)
    {
      novaMatriz[posX][posY - 1] = 2;
    }
    break;
  case 11: // cima, baixo e direita
    if (posX - 1 >= 0 && novaMatriz[posX - 1][posY] == 1)
    {
      novaMatriz[posX - 1][posY] = 2;
    }
    if (posX + 1 < file.linhas && novaMatriz[posX + 1][posY] == 1)
    {
      novaMatriz[posX + 1][posY] = 2;
    }
    if (posY + 1 < file.colunas && novaMatriz[posX][posY + 1] == 1)
    {
      novaMatriz[posX][posY + 1] = 2;
    }
    break;
  case 12: // baixo, esquerda e direita
    if (posX + 1 < file.linhas && novaMatriz[posX + 1][posY] == 1)
    {
      novaMatriz[posX + 1][posY] = 2;
    }
    if (posY - 1 >= 0 && novaMatriz[posX][posY - 1] == 1)
    {
      novaMatriz[posX][posY - 1] = 2;
    }
    if (posY + 1 < file.colunas && novaMatriz[posX][posY + 1] == 1)
    {
      novaMatriz[posX][posY + 1] = 2;
    }
    break;
  }
  return novaMatriz;
}

bool config::aindaTemFogo()
{
  for (int i = 0; i < file.linhas; i++)
  {
    for (int j = 0; j < file.colunas; j++)
    {
      if (matriz[i][j] == 2)
      {
        return true;
      }
    }
  }
  cout << "Não há mais fogo na matriz." << endl;
  return false;
}

