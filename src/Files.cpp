#include "Files.hpp"

vector<vector<short int>> Files::lerMatriz()
{
    try
    {
        ifstream arquivoEntrada("arquivos/input.dat");
        if (!arquivoEntrada)
        {
            throw runtime_error("Arquivo não encontrado");
        }

        string linha;
        if (getline(arquivoEntrada, linha))
        {
            stringstream ss(linha);

            ss >> linhas >> colunas >> focoX >> focoY;

            if (linhas <= 0 || colunas <= 0)
            {
                throw runtime_error("Dimensões da matriz inválidas.");
            }

            // cout << "Linhas: " << linhas << ", Colunas: " << colunas << endl;
            // cout << "FocoX: " << focoX << ", FocoY: " << focoY << endl;

            vector<vector<short int>> matriz(linhas, vector<short int>(colunas));

            for (int i = 0; i < linhas; i++)
            {
                for (int j = 0; j < colunas; j++)
                {
                    arquivoEntrada >> matriz[i][j];
                }
            }
            return matriz;
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << endl;
    }
    return vector<vector<short int>>();
}


void Files::iniciarOutput() {
    arquivoSaida.open("arquivos/output.dat"); 
    if (!arquivoSaida) {
        cerr << "Erro ao criar arquivo de saída!" << endl;
        return;
    }
    arquivoSaida << "RESULTADO DA SIMULAÇÃO: \n\n";
}

void Files::gravarIteracao(int &iteracao, vector<vector<short int>> &matrizFogo) {
    if (!arquivoSaida.is_open()) {
        cerr << "Erro: arquivo de saída não está aberto!" << endl;
        return;
    }

    arquivoSaida << "Iteração: " << iteracao << endl;

    for (short int i = 0; i < linhas; i++) {
        for (short int j = 0; j < colunas; j++) {
            arquivoSaida << matrizFogo[i][j] << " ";
        }
        arquivoSaida << endl;
    }

    arquivoSaida << endl;
}

void Files::movimentoFogo(short int x, short int y, short int valor, short int dx, short int dy){    
    arquivoSaida << "- " << "(" << x << ", " << y << ")" << " vira " << valor;
    string msg = definirDirecao(dx, dy);
    if (msg != "")
    {
        arquivoSaida << " (" << msg << ")";    
    }
    
    arquivoSaida << endl;
}

string Files::definirDirecao(short int &dx, short int &dy){
    if (dx == -1 && dy == 0)
    {
        return "acima";
    }
    else if (dx == 1 && dy == 0)
    {
        return "abaixo";
    }
    else if (dx == 0 && dy == -1)
    {
        return "esquerda";
    }
    else if (dx == 0 && dy == 1)
    {
        return "direita";
    }else if(dx == -1 && dy == -1){
        return "";
    }
    return "direção inválida";
}

void Files::fecharOutput() {
    if (arquivoSaida.is_open()) {
        arquivoSaida.close();
    }
}

void Files::dadosFinaisAnimal(vector<vector<char>> &matrizPassos, short int passos, 
    bool morreu, short int iteracaoMorte, short int encontrouAgua){
    arquivoSaida << "DADOS FINAIS: " << endl;
    arquivoSaida << "Caminho percorrido pelo animal: " << endl;

    for (short int i = 0; i < linhas; i++) {
        for (short int j = 0; j < colunas; j++) {
            arquivoSaida << matrizPassos[i][j] << " ";
        }
        arquivoSaida << endl;
    }
    
    arquivoSaida << "Total de passos: " << passos << endl;
    arquivoSaida << "Quantidade de vezes que encontrou água: " << encontrouAgua << endl;

    arquivoSaida << "Condição final do animal: " << (morreu ? "morreu" : "sobreviveu") << endl;
    if (morreu)
    {
        arquivoSaida << "Iteração em que o animal morreu: " << iteracaoMorte;
    }
    
}