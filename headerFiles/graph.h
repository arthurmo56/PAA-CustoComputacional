#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Estrutura para armazenar lista de adjacência
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** adj;
} Graph;

// Função para criar um grafo
Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->adj = (Node**)malloc(V * sizeof(Node*));
    for (int i = 0; i < V; i++)
        graph->adj[i] = NULL;
    return graph;
}

// Adiciona uma aresta ao grafo (não direcionado)
void addEdge(Graph* graph, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = v;
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = u;
    newNode->next = graph->adj[v];
    graph->adj[v] = newNode;
}

// Função para gerar um grafo aleatório conexo
Graph* generateRandomGraph(int V, int E) {
    if (E < V - 1) {
        printf("Número de arestas insuficiente para garantir conexão!\n");
        return NULL;
    }

    Graph* graph = createGraph(V);
    bool** matrix = (bool**)malloc(V * sizeof(bool*));
    for (int i = 0; i < V; i++) {
        matrix[i] = (bool*)calloc(V, sizeof(bool));
    }

    srand(time(NULL));

    // Garantindo que o grafo seja conexo (criando uma árvore mínima)
    int* visited = (int*)calloc(V, sizeof(int));
    visited[0] = 1; // Começa pelo primeiro vértice

    for (int i = 1; i < V; i++) {
        int u, v;
        do {
            u = rand() % i; // Garante que u é um vértice já visitado
            v = i;         // O próximo vértice a ser conectado
        } while (matrix[u][v]);

        matrix[u][v] = matrix[v][u] = true;
        addEdge(graph, u, v);
        visited[v] = 1;
    }

    // Adicionando arestas extras para alcançar o número desejado de arestas
    int remainingEdges = E - (V - 1);
    while (remainingEdges > 0) {
        int u = rand() % V;
        int v = rand() % V;
        if (u != v && !matrix[u][v]) {
            matrix[u][v] = matrix[v][u] = true;
            addEdge(graph, u, v);
            remainingEdges--;
        }
    }

    for (int i = 0; i < V; i++)
        free(matrix[i]);
    free(matrix);
    free(visited);

    return graph;
}

#endif // GRAPH_H