#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Estrutura do grafo com matriz de adjacência
typedef struct Graph {
    int V;
    int** adj;
} Graph;

// Função para criar um grafo
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (int**)malloc(V * sizeof(int*));
    
    for (int i = 0; i < V; i++) {
        graph->adj[i] = (int*)calloc(V, sizeof(int)); // Inicializa com 0
    }
    
    return graph;
}

// Adiciona uma aresta ao grafo (não direcionado)
void addEdge(Graph* graph, int u, int v) {
    graph->adj[u][v] = 1;
    graph->adj[v][u] = 1;
}

// Função para gerar um grafo aleatório conexo
Graph* generateRandomGraph(int V, int E) {
    if (E < V - 1) {
        printf("Número de arestas insuficiente para garantir conexão!\n");
        return NULL;
    }

    Graph* graph = createGraph(V);
    srand(time(NULL));

    // Garantindo que o grafo seja conexo (criando uma árvore mínima)
    int* visited = (int*)calloc(V, sizeof(int));
    visited[0] = 1; // Começa pelo primeiro vértice

    for (int i = 1; i < V; i++) {
        int u;
        do {
            u = rand() % i; // Garante que u é um vértice já visitado
        } while (graph->adj[u][i]);

        addEdge(graph, u, i);
        visited[i] = 1;
    }

    // Adicionando arestas extras para alcançar o número desejado de arestas
    int remainingEdges = E - (V - 1);
    while (remainingEdges > 0) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && graph->adj[u][v] == 0) {
            addEdge(graph, u, v);
            remainingEdges--;
        }
    }

    free(visited);
    return graph;
}

#endif // GRAPH_H
