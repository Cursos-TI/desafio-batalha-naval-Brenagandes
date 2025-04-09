#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define HABILIDADE_TAM 5

// Função pra imprimir o tabuleiro no console
void mostrarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == 0) printf("~ ");      // Água
            else if (tab[i][j] == 3) printf("N ");  // Navio
            else if (tab[i][j] == 5) printf("* ");  // Habilidade
        }
        printf("\n");
    }
}

// Cria a matriz de habilidade em forma de cone (ponta pra baixo)
void habilidadeCone(int mat[HABILIDADE_TAM][HABILIDADE_TAM]) {
    int meio = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (j >= meio - i && j <= meio + i)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Cruz com origem no meio
void habilidadeCruz(int mat[HABILIDADE_TAM][HABILIDADE_TAM]) {
    int meio = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == meio || j == meio)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Octaedro (losango), soma dos deslocamentos deve ser menor ou igual ao meio
void habilidadeOctaedro(int mat[HABILIDADE_TAM][HABILIDADE_TAM]) {
    int meio = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
}

// Aplica a habilidade no tabuleiro, centralizando na origem
void aplicar(int tab[TAM][TAM], int habilidade[HABILIDADE_TAM][HABILIDADE_TAM], int origemX, int origemY) {
    int offset = HABILIDADE_TAM / 2;
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int linha = origemX + (i - offset);
            int coluna = origemY + (j - offset);

            // Verifica se está dentro dos limites do tabuleiro
            if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                if (habilidade[i][j] == 1 && tab[linha][coluna] == 0) {
                    tab[linha][coluna] = 5; // Marca como área de efeito
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};
    int habilidade[HABILIDADE_TAM][HABILIDADE_TAM];

    // Colocando alguns navios só pra visualizar melhor
    tabuleiro[2][2] = 3;
    tabuleiro[2][3] = 3;
    tabuleiro[4][4] = 3;

    printf("Tabuleiro inicial:\n");
    mostrarTabuleiro(tabuleiro);

    // Testando habilidade cone
    habilidadeCone(habilidade);
    aplicar(tabuleiro, habilidade, 2, 2); // origem no meio da área do cone
    printf("\nHabilidade: CONE\n");
    mostrarTabuleiro(tabuleiro);

    // Cruz em outra posição
    habilidadeCruz(habilidade);
    aplicar(tabuleiro, habilidade, 6, 6);
    printf("\nHabilidade: CRUZ\n");
    mostrarTabuleiro(tabuleiro);

    // Octaedro
    habilidadeOctaedro(habilidade);
    aplicar(tabuleiro, habilidade, 5, 2);
    printf("\nHabilidade: OCTAEDRO\n");
    mostrarTabuleiro(tabuleiro);

    return 0;
}
