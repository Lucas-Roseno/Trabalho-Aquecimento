#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;
class Files {
    public:
        int linhas, colunas, focoX, focoY;
        vector<vector<int>> lerMatriz();

};