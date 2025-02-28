#ifndef TARJAN_H
#define TARJAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "graph.h"

// Variável global para contar pontes
int bridgeCount = 0;

// Função auxiliar da DFS para encontrar pontes
void dfsBridge(Graph* graph, int u, int parent, int* disc, int* low, bool* visited, int* time) {
    visited[u] = true;
    disc[u] = low[u] = ++(*time);

    Node* temp = graph->adj[u];
    while (temp != NULL) {
        int v = temp->dest;

        if (!visited[v]) {
            dfsBridge(graph, v, u, disc, low, visited, time);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if (low[v] > disc[u]) {
                printf("Ponte encontrada: %d - %d\n", u, v);
                bridgeCount++;  // Incrementa a contagem de pontes
            }
        } else if (v != parent) {
            low[u] = (low[u] < disc[v]) ? low[u] : disc[v];
        }

        temp = temp->next;
    }
}

// Função para encontrar pontes em um grafo usando Tarjan
void findBridges(Graph* graph) {
    int* disc = (int*)malloc(graph->V * sizeof(int));
    int* low = (int*)malloc(graph->V * sizeof(int));
    bool* visited = (bool*)malloc(graph->V * sizeof(bool));

    for (int i = 0; i < graph->V; i++) {
        disc[i] = -1;
        low[i] = -1;
        visited[i] = false;
    }

    int time = 0;
    bridgeCount = 0;  // Reseta a contagem

    for (int i = 0; i < graph->V; i++) {
        if (!visited[i])
            dfsBridge(graph, i, -1, disc, low, visited, &time);
    }

    free(disc);
    free(low);
    free(visited);
}

#endif  // TARJAN_H