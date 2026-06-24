Repositório dedicado às implementações práticas da disciplina de Cálculo Numérico. O objetivo é resolver problemas clássicos de Álgebra Linear utilizando algoritmos otimizados em linguagem C.

---

## 🎯 Sobre os Projetos

Este repositório contém dois trabalhos principais:

1. **Trabalho 1: Determinante por Eliminação de Gauss (Pivotação Parcial)**
   * Transforma a matriz original em uma matriz triangular superior.
   * Utiliza a técnica de pivotação parcial (buscando o maior valor absoluto na coluna) para minimizar erros de arredondamento causados por pontos flutuantes.
   * Calcula o determinante multiplicando a diagonal principal e ajustando o sinal com base no número de trocas de linhas realizadas.

2. **Trabalho 2: Sistema Linear por Gauss-Seidel**
   * Resolve sistemas lineares através de um método iterativo.
   * Utiliza o **Erro Relativo** como critério de parada, garantindo que a diferença entre as iterações seja menor que a precisão ($\varepsilon$) exigida.
   * Atualiza as variáveis na mesma iteração, otimizando a convergência em relação ao método de Jacobi.

---

## 📁 Estrutura de Arquivos

* `gauss_determinante.c` : Código-fonte do Trabalho 1 (Eliminação de Gauss).
* `gauss_seidel.c` : Código-fonte do Trabalho 2 (Método de Gauss-Seidel).
* `README.md` : Documentação do projeto.

---

## ⚙️ Como Compilar e Executar

Como os códigos fazem uso da biblioteca matemática padrão do C (`<math.h>` para a função `fabs`), no linux é estritamente necessário utilizar a flag `-lm` durante a compilação no GCC.

Abra o seu terminal e execute os comandos abaixo:

### Para o Trabalho 1 (Gauss)

# Compilando
gcc gauss_determinante.c -o gauss -lm

# Executando
./gauss

### Para o Trabalho 2 (Gauss-Seidel)

# Compilando
gcc gauss_seidel.c -o seidel -lm

# Executando
./seidel

# Como Usar

Ao executar qualquer um dos programas, o terminal solicitará as informações passo a passo:

Digite a ordem da matriz (ex: 3 para uma matriz 3x3).

Insira os coeficientes linha por linha.

Insira os termos independentes (no caso de sistemas lineares).

No método iterativo, insira a precisão desejada (ex: 0.01) e o vetor de chute inicial.

O programa exibirá o passo a passo de cada iteração, as matrizes formatadas e o tempo total de execução na tela.

Feito por Vinícius, estudante de Ciência da Computação pela UEMS.
