#include "Files.hpp"

vector<vector<int>> Files::lerMatriz()
{
    try
    {
        ifstream arquivoEntrada("input.dat");
        if (!arquivoEntrada)
        {
            throw runtime_error("Arquivo não encontrado");
        }

        string linha;
        if (getline(arquivoEntrada, linha))
        {
            stringstream ss(linha);
            
            ss >> linhas >> colunas >> focoX >> focoY;

            vector<vector<int>> matriz(linhas, vector<int>(colunas));

            for(int i = 0; i < linhas; i++){
                for(int j = 0; j < colunas; j++){
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
    return vector<vector<int>>();
}