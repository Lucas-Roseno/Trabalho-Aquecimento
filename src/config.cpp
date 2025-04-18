#include "config.hpp"

void config::executarSimulacao()
{

  matriz = file.lerMatriz();
  matriz[file.focoX][file.focoY] = 2;

  cout << "\nMatriz de entrada:" << endl;
  imprimirMatriz();

  animal.inicializador(matriz, file);
  cout << "Posição do animal: " << animal.getPosicaoAtual().first << ", "
       << animal.getPosicaoAtual().second << endl;
  imprimirMatriz();

  while (aindaTemFogo() && iteracao < IteracoesMax)
  {
    if (!animal.morreu)
    {
      animal.movimentar(matriz, file, false);
    }
    
    cout << "ITERAÇÃO " << iteracao << ":" << endl;
    cout << "Movimentação do animal: " << endl;
    imprimirMatriz();
    

    //apaga os fogos da última iteração
    for (const auto &fogo : fogoInicial)
    {
      matriz[fogo.first][fogo.second] = 3;
    }

    propagacaoFogo();

    cout << "Movimentação do fogo: " << endl;
    imprimirMatriz();

    iteracao++;
  }
  cout << "Caminho percorrido pelo animal: " << endl;
  animal.mostrarCaminho();
  cout << "Total de passos: " << animal.passos << endl;
}

void config::imprimirMatriz()
{
  for (const auto &linha : matriz)
  {
    for (const auto &elemento : linha)
    {
      cout << elemento << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

void config::propagacaoFogo()
{
  fogoInicial.clear();
  vector<vector<short int>> novaMatriz = matriz;

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

vector<vector<short int>> config::espalharFogo(int posX, int posY, vector<vector<short int>> novaMatriz)
{
  // Define as direções permitidas para cada tipo de vento
  static const vector<vector<pair<int, int>>> direcoesVento = {
      {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}, // 0: sem vento
      {{-1, 0}},                          // 1: cima
      {{1, 0}},                           // 2: baixo
      {{0, -1}},                          // 3: esquerda
      {{0, 1}},                           // 4: direita
      {{-1, -1}},                         // 5: cima e esquerda
      {{-1, 1}},                          // 6: cima e direita
      {{1, -1}},                          // 7: baixo e esquerda
      {{1, 1}},                           // 8: baixo e direita
      {{-1, 0}, {0, -1}, {0, 1}},         // 9: cima, esquerda e direita
      {{-1, 0}, {1, 0}, {0, -1}},         // 10: cima, baixo e esquerda
      {{-1, 0}, {1, 0}, {0, 1}},          // 11: cima, baixo e direita
      {{1, 0}, {0, -1}, {0, 1}}           // 12: baixo, esquerda e direita
  };

  for (const auto &dir : direcoesVento[direcaoVento])
  {
    int auxX = posX + dir.first;
    int auxY = posY + dir.second;

    if (auxX >= 0 && auxX < file.linhas &&
        auxY >= 0 && auxY < file.colunas &&
        novaMatriz[auxX][auxY] == 9 && animal.valorAnterior == 1)
    {
      
      
      //Faz a movimentação podendo acessar as casas já visitadas
      animal.movimentar(novaMatriz, file, true);
      //Se nesse caso retornar -1, significa que o animal está cercado e casa atual é diferente de 0
      if (animal.valorI == -1)
      {
        if (animal.valorAnterior == 0 || animal.tempoParado > 3)
        {
            cout << "Como o valor da casa é 0 ele pode ficar parado por 3 iterações" << endl;
            cout << "Número de iterações parado: " << animal.tempoParado;
        }else{
            cout << "Não há casas sem fogo ao redor e a casa atual é igual a 1." << endl;
            cout << "Animal morreu!" << endl;
            animal.morreu = true;
            animal.iteracaoMorte = iteracao;
        }
      }else{
        cout << "Fogo atingiu a casa do animal e ele deu o 2 movimento." << endl;
      }

      novaMatriz[auxX][auxY] = 2;

      for (const auto &linha : novaMatriz)
      {
        for (const auto &elemento : linha)
        {
          cout << elemento << " ";
        }
        cout << "\n";
      }
      cout << "\n";
    }

    if (auxX >= 0 && auxX < file.linhas &&
        auxY >= 0 && auxY < file.colunas &&
        novaMatriz[auxX][auxY] == 1)
    {
      novaMatriz[auxX][auxY] = 2;
    }
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
