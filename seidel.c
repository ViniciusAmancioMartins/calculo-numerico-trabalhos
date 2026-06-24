#include <stdio.h>
#include <stdlib.h>
#include <math.h>   // Necessário para o fabs() (módulo)
#include <time.h>   // Necessário para o clock()

// Apenas exibe o sistema na tela para conferência visual
void imprimirSistema(double A[10][10], double b[10], int n) {
    printf("\nSistema Linear Inicial (A | b):\n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%9.7f ", A[i][j]); // %9.7f alinha as colunas
        }
        printf("| %9.7f\n", b[i]);
    }
    printf("\n");
}

// O motor matemático do Gauss-Seidel
void resolverGaussSeidel(double A[10][10], double b[10], double x[10], int n, double precisao) {
    double x_novo[10]; // Vetor rascunho para os cálculos da rodada atual
    
    // Valor inicial falso apenas para garantir que o while rode a primeira vez
    double erro = precisao + 1.0; 
    
    int iteracao = 1;
    int max_iteracoes = 500; // Trava de segurança contra loops infinitos

    printf("Iteracao 0 (Solucao Inicial):\n");
    for(int i = 0; i < n; i++) {
        printf("x[%d] = %.7f\n", i + 1, x[i]);
    }
    printf("\n");

    // Condição de parada: Erro tem que ficar menor que a precisão
    while (erro > precisao && iteracao <= max_iteracoes) {
        double max_dif = 0.0;     // Guardará o numerador do erro relativo
        double max_x_novo = 0.0;  // Guardará o denominador do erro relativo

        for (int i = 0; i < n; i++) {
            double soma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) { // Ignora a diagonal principal (ela é quem será isolada)
                    
                    // Coração de todo o método de Gauss-Seidel:
                    if (j < i) {
                        soma += A[i][j] * x_novo[j]; // Usa o valor recém-atualizado nesta mesma rodada
                    } else {
                        soma += A[i][j] * x[j];      // Usa o valor da rodada anterior
                    }
                }
            }

            // Isola a variável (passa dividindo pelo termo da diagonal principal)
            x_novo[i] = (b[i] - soma) / A[i][i];

            // Calcula a diferença em módulo para esta variável específica
            double dif = fabs(x_novo[i] - x[i]);
            
            // Atualiza os maiores valores encontrados para o cálculo do erro final
            if (dif > max_dif) {
                max_dif = dif;
            }
            if (fabs(x_novo[i]) > max_x_novo) {
                max_x_novo = fabs(x_novo[i]);
            }
        }

        // Calcula o Erro Relativo (maior diferença dividida pelo maior elemento)
        if (max_x_novo != 0) {
            erro = max_dif / max_x_novo;
        } else {
            erro = max_dif; // Evita divisão por zero
        }

        printf("Iteracao %d:\n", iteracao);
        for(int i = 0; i < n; i++) {
            printf("x[%d] = %.7f\n", i + 1, x_novo[i]);
        }
        printf("Erro = %.7f\n\n", erro);

        // Fim da rodada: os valores novos viram os velhos para a próxima iteração
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
    double A[10][10], b[10], x[10], precisao;

    printf("--- Trabalho 2: Sistema Linear por Gauss-Seidel ---\n");
    printf("Digite a ordem da matriz dos coeficientes (maximo 10): ");
    scanf("%d", &n);

    if(n > 10 || n <= 0) {
        printf("Erro: Ordem invalida.\n");
        return 1; // Encerra o programa se a entrada for absurda
    }

    printf("Digite as equacoes (coeficientes e depois o termo independente b):\n");
    for (int i = 0; i < n; i++) {
        printf("Equacao %d:\n", i + 1);
        for (int j = 0; j < n; j++) {
            printf(" A[%d][%d]: ", i + 1, j + 1);
            scanf("%lf", &A[i][j]); // %lf carrega as matrizes de double
        }
        printf(" b[%d]: ", i + 1);
        scanf("%lf", &b[i]);
    }

    // Trava para impedir precisões negativas (ex: loop infinito se digitar -1)
    do {
        printf("\nDigite a precisao desejada (deve ser maior que 0, ex: 0.001): ");
        scanf("%lf", &precisao);
        if (precisao <= 0) printf("A precisao deve ser um valor positivo!\n");
    } while (precisao <= 0);

    printf("Digite o vetor de solucao inicial:\n");
    for (int i = 0; i < n; i++) {
        printf(" x[%d]: ", i + 1);
        scanf("%lf", &x[i]);
    }

    imprimirSistema(A, b, n);

    clock_t inicio = clock(); // Dispara o cronômetro
    
    resolverGaussSeidel(A, b, x, n, precisao);
    
    clock_t fim = clock();    // Para o cronômetro
    
    // Converte os ciclos de processamento em segundos
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nTempo de execucao: %f segundos\n", tempo_execucao);

    return 0;
}
