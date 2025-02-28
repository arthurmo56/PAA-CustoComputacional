#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "headerFiles/tarjan.h"



int main() {
    int V;
    int E;

    scanf("%d", &V); // Número de vértices
   
    scanf("%d", &E); // Número de arestas
 

    // Grafo do enunciado
    /*
    Graph* graph = createGraph(V);
    addEdge(graph,0,1);
    addEdge(graph,0,4);
    addEdge(graph,0,3);
    addEdge(graph,1,3);
    addEdge(graph,1,4);
    addEdge(graph,1,2);
    addEdge(graph,2,4);
    addEdge(graph,2,3);
    addEdge(graph,2,5);
    addEdge(graph,3,5);
    addEdge(graph,4,5);
    addEdge(graph,6,5);
    addEdge(graph,6,7);
    addEdge(graph,6,8);
    addEdge(graph,7,8);
    */
    
    Graph* graph = generateRandomGraph(V, E);

    /*
    
        a função generateRandomGraph gera um grafo aleatório conexo
        com V vértices e E arestas, agora so falta implementar o 
        algoritmo de naive e aplicar fleury nos dois e comparar os 
        resultados

        TODO:
            - implementar algoritmo de naive
            - adicionar o algoritmo de fleury
    
    */

    printf("Procurando pontes no grafo aleatorio...\n");

    // Medir tempo de execução
    clock_t start = clock();
    findBridges(graph);
    clock_t end = clock();

    printf("\nTotal de pontes encontradas: %d\n", bridgeCount);
    printf("Tempo de execucao: %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}