#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Função auxiliar para imprimir a matriz com 2 casas decimais
void imprimirMatriz(double mat[10][10], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para calcular e imprimir o determinante final
void calculaDeterminante(double mat[10][10], int n, int trocas) {
    double det = 1.0;
    
    printf("--- Calculo do Determinante ---\n");
    printf("Det = ");
    
    if (trocas % 2 != 0) {
        printf("(-1) * ");
        det = -1.0;
    }
    
    // Multiplica a diagonal principal
    for (int i = 0; i < n; i++) {
        printf("(%.2f)", mat[i][i]);
        det *= mat[i][i];
        if (i < n - 1) {
            printf(" * ");
        }
    }
    printf("\n");
    printf("Determinante Final = %.2f\n\n", det);
}

// Função que realiza a eliminação de Gauss e pivotação parcial
void eliminacaoGauss(double mat[10][10], int n, int *trocas) {
    printf("\nMatriz Inicial:\n");
    imprimirMatriz(mat, n);

    for (int k = 0; k < n - 1; k++) {
        // Encontra o pivô (maior valor absoluto na coluna k, da linha k para baixo)
        int max_idx = k;
        double max_val = fabs(mat[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(mat[i][k]) > max_val) {
                max_val = fabs(mat[i][k]);
                max_idx = i;
            }
        }

        // Realiza a troca de linhas, se o pivô não estiver na linha atual
        if (max_idx != k) {
            for (int j = 0; j < n; j++) {
                double temp = mat[k][j];
                mat[k][j] = mat[max_idx][j];
                mat[max_idx][j] = temp;
            }
            (*trocas)++; // Registra a troca para inverter o sinal do determinante depois
            printf("Troca da linha %d com a linha %d:\n", k + 1, max_idx + 1);
            imprimirMatriz(mat, n);
        }

        // Processo de eliminação (zerar elementos abaixo do pivô)
        for (int i = k + 1; i < n; i++) {
            double m = -mat[i][k] / mat[k][k];
            mat[i][k] = 0.0; // Zera explicitamente por conta de arredondamento do computador
            
            for (int j = k + 1; j < n; j++) {
                mat[i][j] = mat[i][j] + m * mat[k][j];
            }
        }
        
        printf("Iteracao %d (Zerando coluna %d):\n", k + 1, k + 1);
        imprimirMatriz(mat, n);
    }
}

int main() {
    int n;
    double mat[10][10];
    int trocas = 0;

    printf("--- Trabalho 1: Determinante por Gauss (Pivotacao Parcial) ---\n");
    printf("Digite a ordem da matriz (maximo 10): ");
    scanf("%d", &n);

    if (n > 10 || n <= 0) {
        printf("Erro: Ordem invalida. Deve ser entre 1 e 10.\n");
        return 1;
    }

    printf("Digite os elementos da matriz linha por linha:\n");
    for (int i = 0; i < n; i++) {
        printf("Linha %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    clock_t inicio = clock();
    
    // Chamadas modulares organizadas no main
    eliminacaoGauss(mat, n, &trocas);
    calculaDeterminante(mat, n, trocas);
    
    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Tempo de execucao: %f segundos\n", tempo_execucao);

    return 0;
}
