#include "config.hpp"

void config::executarSimulacao()
{
  matriz = file.lerMatriz();
  matriz[file.focoX][file.focoY] = 2;
  cout << "Iteracao 0:" << endl;
  imprimirMatriz();

  while (aindaTemFogo() && iteracao < 7)
  {
    jaQueimou = vector<vector<bool>>(file.linhas, vector<bool>(file.colunas, false));
    cout << "Iteracao " << iteracao << ":" << endl;

    propagacaoFogo();
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
}

void config::propagacaoFogo()
{
  vector<vector<int>> novaMatriz = matriz;
  for (int i = 0; i < file.linhas; i++)
  {
    for (int j = 0; j < file.colunas; j++)
    {
      if (matriz[i][j] == 2)
      {
        novaMatriz = espalharFogo(i, j, novaMatriz);
      }
    }
  }
  matriz = novaMatriz;
  imprimirMatriz();

  for (int i = 0; i < file.linhas; i++)
  {
    for (int j = 0; j < file.colunas; j++)
    {
      if(jaQueimou[i][j] == true){
        matriz[i][j] = 3;
      }
    }
  }
}

vector<vector<int>> config::espalharFogo(int posX, int posY, vector<vector<int>> novaMatriz)
{
  for (int i = 0; i < 4; i++)
  {
    if (posX + dx[i] >= 0 && posX + dx[i] < file.linhas &&
        posY + dy[i] >= 0 && posY + dy[i] < file.colunas &&
        novaMatriz[posX + dx[i]][posY + dy[i]] == 1)
    {
      novaMatriz[posX + dx[i]][posY + dy[i]] = 2;
    }
    
    jaQueimou[posX][posY] = true;
    
    
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
        cout << "Ainda há fogo na posição (" << i << "," << j << ")" << endl;
        return true;
      }
    }
  }
  cout << "Não há mais fogo na matriz." << endl;
  return false;
}

