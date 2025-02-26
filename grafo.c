#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_VERTICES 5

// inicializar a matriz de adjacência com zeros
void inicializarMatriz(int matriz[NUM_VERTICES][NUM_VERTICES]) {
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            matriz[i][j] = 0;
        }
    }
}

//  gerar um grafo aleatório
void gerarGrafoAleatorio(int matriz[NUM_VERTICES][NUM_VERTICES]) {
    srand(time(NULL)); 
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = i + 1; j < NUM_VERTICES; j++) {
            int aresta = rand() % 2;
            matriz[i][j] = aresta;
            matriz[j][i] = aresta; // O grafo é não direcionado, então a matriz é simétrica
        }
    }
}

// exibir a matriz de adjacência
void exibirMatriz(int matriz[NUM_VERTICES][NUM_VERTICES]) {
    printf("Matriz de Adjacencia:\n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        for (int j = 0; j < NUM_VERTICES; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// exibir as ligações das arestas
void exibirLigacoes(int matriz[NUM_VERTICES][NUM_VERTICES]) {
    
    printf("\n");
    for (int i = 0; i < NUM_VERTICES; i++) {
        printf("Vertice %d: ( ", i);
        for (int j = 0; j < NUM_VERTICES; j++) {
            if (matriz[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf(")");
        printf("\n");
    }
}

int main() {
    int matriz[NUM_VERTICES][NUM_VERTICES];

    inicializarMatriz(matriz);
    gerarGrafoAleatorio(matriz);
    exibirMatriz(matriz);
    exibirLigacoes(matriz);

    return 0;
}