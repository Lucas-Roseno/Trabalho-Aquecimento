#include "Files.hpp"

vector<vector<short int>> Files::lerMatriz()
{
    try
    {
        ifstream arquivoEntrada("src/input.dat");
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