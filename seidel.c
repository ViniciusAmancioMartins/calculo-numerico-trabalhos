#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Função para imprimir o sistema linear no início
void imprimirSistema(double A[10][10], double b[10], int n) {
    printf("\nSistema Linear Inicial (A | b):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%9.7f ", A[i][j]);
        }
        printf("| %9.7f\n", b[i]);
    }
    printf("\n");
}

// Função principal do método Gauss-Seidel
void resolverGaussSeidel(double A[10][10], double b[10], double x[10], int n, double precisao) {
    double x_novo[10];
    
    // Inicializamos o erro com um valor propositalmente maior que a precisão 
    // para garantir que o laço while execute a primeira iteração.
    double erro = precisao + 1.0; 
    
    int iteracao = 1;
    int max_iteracoes = 500; // Limite de segurança

    printf("Iteracao 0 (Solucao Inicial):\n");
    for(int i = 0; i < n; i++) {
        printf("x[%d] = %.7f\n", i + 1, x[i]);
    }
    printf("\n");

    while (erro > precisao && iteracao <= max_iteracoes) {
        double max_dif = 0.0;
        double max_x_novo = 0.0;

        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    if (j < i) {
                        soma += A[i][j] * x_novo[j];
                    } else {
                        soma += A[i][j] * x[j];
                    }
                }
            }

            x_novo[i] = (b[i] - soma) / A[i][i];

            double dif = fabs(x_novo[i] - x[i]);
            if (dif > max_dif) {
                max_dif = dif;
            }
            if (fabs(x_novo[i]) > max_x_novo) {
                max_x_novo = fabs(x_novo[i]);
            }
        }

        if (max_x_novo != 0) {
            erro = max_dif / max_x_novo;
        } else {
            erro = max_dif;
        }

        printf("Iteracao %d:\n", iteracao);
        for(int i = 0; i < n; i++) {
            printf("x[%d] = %.7f\n", i + 1, x_novo[i]);
        }
        printf("Erro = %.7f\n\n", erro);

        for(int i = 0; i < n; i++) {
            x[i] = x_novo[i];
        }

        iteracao++;
    }

    if (iteracao > max_iteracoes) {
        printf("--- Atencao: O limite de iteracoes foi atingido sem convergir! ---\n");
    } else {
        printf("--- Solucao Final Alcancada ---\n");
    }
    
    for(int i = 0; i < n; i++) {
        printf("x[%d] = %.7f\n", i + 1, x[i]);
    }
}

int main() {
    int n;
    double A[10][10];
    double b[10];
    double x[10];
    double precisao;

    printf("--- Trabalho 2: Sistema Linear por Gauss-Seidel ---\n");
    printf("Digite a ordem da matriz dos coeficientes (maximo 10): ");
    scanf("%d", &n);

    if(n > 10 || n <= 0) {
        printf("Erro: Ordem invalida.\n");
        return 1;
    }

    printf("Digite as equacoes (coeficientes e depois o termo independente b):\n");
    for (int i = 0; i < n; i++) {
        printf("Equacao %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf(" A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &A[i][j]);
        }
        printf(" b[%d]: ", i + 1);
        scanf("%lf", &b[i]);
    }

    // Validação para garantir que a precisão seja maior que zero
    do {
        printf("\nDigite a precisao desejada (deve ser maior que 0, ex: 0.001): ");
        scanf("%lf", &precisao);
        if (precisao <= 0) {
            printf("A precisao deve ser um valor positivo!\n");
        }
    } while (precisao <= 0);

    printf("Digite o vetor de solucao inicial:\n");
    for (int i = 0; i < n; i++) {
        printf(" x[%d]: ", i + 1);
        scanf("%lf", &x[i]);
    }

    imprimirSistema(A, b, n);

    clock_t inicio = clock();
    
    resolverGaussSeidel(A, b, x, n, precisao);
    
    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("\nTempo de execucao: %f segundos\n", tempo_execucao);

    return 0;
}