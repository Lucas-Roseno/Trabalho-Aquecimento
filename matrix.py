import random

def gerar_matriz(linhas, colunas):
    return [[random.choices([0, 1, 4], weights=[1, 3, 0.1])[0] for _ in range(colunas)] for _ in range(linhas)]

def imprimir_matriz(matriz):
    for linha in matriz:
        print(" ".join(map(str, linha)))

def salvar_matriz_em_arquivo(matriz, arquivo):
    with open(arquivo, "w") as f:
        f.write(f"{len(matriz)} {len(matriz[0])} 1 1\n")  # Adiciona dimensões e posição inicial
        for linha in matriz:
            f.write(" ".join(map(str, linha)) + "\n")

if __name__ == "__main__":
    linhas = int(input("Digite o número de linhas: "))
    colunas = int(input("Digite o número de colunas: "))
    matriz = gerar_matriz(linhas, colunas)
    imprimir_matriz(matriz)
    salvar_matriz_em_arquivo(matriz, "src/input.dat")
    print("\nMatriz salva no arquivo 'input.dat'.")
