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

// Função para gerar um grafo aleatório
Graph* generateRandomGraph(int V, int E) {
    Graph* graph = createGraph(V);
    bool** matrix = (bool**)malloc(V * sizeof(bool*));
    
    for (int i = 0; i < V; i++) {
        matrix[i] = (bool*)calloc(V, sizeof(bool));
    }

    srand(time(NULL));

    for (int i = 0; i < E; i++) {
        int u, v;
        do {
            u = rand() % V;
            v = rand() % V;
        } while (u == v || matrix[u][v]);  // Evita laços e arestas duplicadas

        matrix[u][v] = matrix[v][u] = true;
        addEdge(graph, u, v);
    }

    for (int i = 0; i < V; i++)
        free(matrix[i]);
    free(matrix);

    return graph;
}

// Função principal
int main() {
    int V = 9; // Número de vértices
//  int E =  9999; // Número de arestas

    // Grafo do enunciado
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
    

    /*
    
        O algoritmo está funcionando corretamente, porém ao gerar grafos aleatorios
        será necessario garantir que o grafo seja conexo para conseguir executar o
        fleury
        
        TODO:
            - mudar função geradora de grafos aleatorios para garantir conectividade
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
