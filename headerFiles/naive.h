#ifndef NAIVE_H
#define NAIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "graph.h"

// Função auxiliar para DFS
void dfs(Graph* graph, int v, bool* visited) {
    visited[v] = true;
    for (int u = 0; u < graph->V; u++) {
        if (graph->adj[v][u] == 1 && !visited[u]) {
            dfs(graph, u, visited);
        }
    }
}

// Função para verificar se o grafo é conexo
bool isConnected(Graph* graph) {
    bool* visited = (bool*)calloc(graph->V, sizeof(bool));
    
    // Encontra o primeiro vértice com arestas
    int start = -1;
    for (int i = 0; i < graph->V; i++) {
        for (int j = 0; j < graph->V; j++) {
            if (graph->adj[i][j] == 1) {
                start = i;
                break;
            }
        }
        if (start != -1) break;
    }

    if (start == -1) {
        free(visited);
        return false; // Nenhuma aresta, então não é conexo
    }

    dfs(graph, start, visited);

    // Verifica se todos os vértices foram visitados
    for (int i = 0; i < graph->V; i++) {
        if (!visited[i]) {
            free(visited);
            return false;
        }
    }
    
    free(visited);
    return true;
}

// Função que usa o método naïve para testar pontes
void naiveFindBridges(Graph* graph) {
    printf("Buscando pontes usando método naïve:\n");
    for (int u = 0; u < graph->V; u++) {
        for (int v = u + 1; v < graph->V; v++) {
            if (graph->adj[u][v] == 1) {
                // Remove a aresta
                graph->adj[u][v] = 0;
                graph->adj[v][u] = 0;
                
                // Testa se o grafo ainda é conexo
                if (!isConnected(graph)) {
                    printf("Ponte encontrada: %d - %d\n", u, v);
                }
                
                // Restaura a aresta
                graph->adj[u][v] = 1;
                graph->adj[v][u] = 1;
            }
        }
    }
}

#endif  // NAIVE_H
