import random

def gerar_matriz(linhas, colunas):
    return [[random.choices([0, 1, 4], weights=[1, 3, 0.1])[0] for _ in range(colunas)] for _ in range(linhas)]

def salvar_matriz_em_arquivo(matriz, arquivo):
    with open(arquivo, "w") as f:
        f.write(f"{len(matriz)} {len(matriz[0])} 1 1\n")  
        for linha in matriz:
            f.write(" ".join(map(str, linha)) + "\n")

if __name__ == "__main__":
    linhas = int(input("Digite o número de linhas: "))
    colunas = int(input("Digite o número de colunas: "))
    matriz = gerar_matriz(linhas, colunas)
    salvar_matriz_em_arquivo(matriz, "arquivos/input.dat")
    print("\nMatriz salva no arquivo 'input.dat'.")
