#include "config.hpp"

void config::executarSimulacao()
{
  matriz = file.lerMatriz();
  matriz[file.focoX][file.focoY] = 2;
  file.iniciarOutput();

  cout << "\nMatriz de entrada:" << endl;
  imprimirMatriz(matriz);

  animal.inicializador(matriz, file);
  imprimirMatriz(animal.matrizAnimal);

  while (aindaTemFogo() && iteracao < IteracoesMax)
  {
    if (!animal.morreu)
    {
      animal.movimentar(matriz, file, false);
    }

    cout << "\nITERAÇÃO " << iteracao << ":" << endl;
    if (!animal.morreu)
    {
      cout << "Movimentação do animal: " << endl;
      imprimirMatriz(animal.matrizAnimal);
    }

    // apaga os fogos da última iteração
    for (const auto &fogo : fogoInicial)
    {
      matriz[fogo.first][fogo.second] = 3;
      file.movimentoFogo(fogo.first, fogo.second, 3, -1, -1);
    }

    propagacaoFogo();

    if (animal.apagouFogo)
    {
      dispersarUmidade(animal.posicaoAtual.first, animal.posicaoAtual.second);
    }

    cout << "Movimentação do fogo: " << endl;
    imprimirMatriz(matriz);

    cout << "====================================" << endl;

    iteracao++;

    file.gravarIteracao(iteracao, matriz);
  }

  cout << "Caminho percorrido pelo animal: " << endl;
  atualizarMatrizPassos();
  cout << "Total de passos: " << animal.passos << endl;
  cout << "Quantidade de vezes que encontrou água: " << animal.encontrouAgua << endl;

  cout << "Condição final do animal: " << (animal.morreu ? "morreu" : "sobreviveu") << endl;
  if (animal.morreu)
  {
    cout << "Iteração em que o animal morreu: " << animal.iteracaoMorte;
  }

  file.dadosFinaisAnimal(animal.matrizPassos, animal.passos, animal.morreu,
                         animal.iteracaoMorte, animal.encontrouAgua);

  file.fecharOutput();
}

void config::imprimirMatriz(vector<vector<short int>> &matriz)
{
  for (const auto &linha : matriz)
  {
    for (const auto &elemento : linha)
    {
      switch (elemento)
      {
      case 0:
        cout << "\U0001FAA8  "; // 🪨 (Espaço vazio)
        break;
      case 1:
        cout << "\U0001F332 "; // 🌲 (Árvore)
        break;
      case 2:
        cout << "\U0001F525 "; // 🔥 (Fogo)
        break;
      case 3:
        cout << "\U00002B1B "; //  (Bloco preto)
        break;
      case 4:
        cout << "\U0001F4A7 "; // 💧 (Água)
        break;
      case 9:
        cout << "\U0001F412 "; // 🐒 (Animal) 
        break;
      }
    }
    cout << "\n";
  }
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
  vector<vector<pair<short int, short int>>> direcoesVento = {
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
      {{1, 0}, {0, -1}, {0, 1}},          // 12: baixo, esquerda e direita
      {{0, -1}, {0, 1}},                  // 13: esquerda e direita
      {{-1, 0}, {1, 0}}                   // 14: cima e baixo
  };

  for (const auto &dir : direcoesVento[direcaoVento])
  {
    short int auxX = posX + dir.first;
    short int auxY = posY + dir.second;

    if (auxX >= 0 && auxX < file.linhas &&
        auxY >= 0 && auxY < file.colunas &&
        animal.matrizAnimal[auxX][auxY] == 9 && animal.valorAnterior == 1)
    // Animal em posição que vai ser incendiada
    {

      animal.movimentar(novaMatriz, file, true); // 2 movimento, acessando casas visitadas

      // Se valorI = -1 -> animal cercado
      if (animal.valorI == -1)
      {
        if (animal.valorAnterior == 0 && animal.tempoParado < 3)
        {
          cout << "Como o valor da casa é 0 ele pode ficar parado por 3 iterações" << endl;
          cout << "Número de iterações parado: " << animal.tempoParado;
        }
        else
        {
          cout << "Não há casas sem fogo ao redor e a casa atual é igual a 1." << endl;
          cout << "Animal morreu!" << endl;
          animal.morreu = true;
          animal.iteracaoMorte = iteracao;
        }
      }
      else
      {
        cout << "Fogo atingiu a casa do animal e ele deu o 2 movimento." << endl;
      }

      novaMatriz[auxX][auxY] = 2;
      animal.matrizAnimal[auxX][auxY] = 2;
      file.movimentoFogo(auxX, auxY, 2, dir.first, dir.second);

      imprimirMatriz(animal.matrizAnimal);
      cout << "\n";
    }

    if (auxX >= 0 && auxX < file.linhas &&
        auxY >= 0 && auxY < file.colunas &&
        novaMatriz[auxX][auxY] == 1)
    {
      novaMatriz[auxX][auxY] = 2;
      file.movimentoFogo(auxX, auxY, 2, dir.first, dir.second);
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

void config::dispersarUmidade(short int &x, short int &y)
{
  matriz[x][y] = 0;
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

void config::atualizarMatrizPassos()
{
  for (short int i = 0; i < file.linhas; i++)
  {
    for (short int j = 0; j < file.colunas; j++)
    {
      if (animal.matrizPassos[i][j] != '*' && animal.matrizPassos[i][j] != '9')
      {
        animal.matrizPassos[i][j] = static_cast<char>(matriz[i][j] + '0');
      }
      cout << animal.matrizPassos[i][j] << " ";
    }
    cout << endl;
  }
}
