#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VERTICES 5

// Estrutura para representar um nó na lista de adjacências
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// Estrutura para representar um grafo
typedef struct Graph {
    Node* adjList[VERTICES];
} Graph;

// Função para criar um novo nó
Node* createNode(int vertex) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Função para inicializar um grafo
void initGraph(Graph* graph) {
    for (int i = 0; i < VERTICES; i++) {
        graph->adjList[i] = NULL;
    }
}

// Função para gerar um grafo aleatório
void generateRandomGraph(Graph* graph) {
    srand(time(NULL));
    int numEdges = rand() % (VERTICES * (VERTICES - 1) / 2) + 1;
    
    for (int i = 0; i < numEdges; i++) {
        int v1 = rand() % VERTICES;
        int v2 = rand() % VERTICES;
        
        if (v1 != v2) {
            // Verifica se a aresta já existe
            Node* temp = graph->adjList[v1];
            int exists = 0;
            while (temp) {
                if (temp->vertex == v2) {
                    exists = 1;
                    break;
                }
                temp = temp->next;
            }
            
            if (!exists) {
                addEdge(graph, v1, v2);
            }
        }
    }
}

// Função para imprimir o grafo
void printGraph(Graph* graph) {
    for (int i = 0; i < VERTICES; i++) {
        printf("Vértice %d: ", i);
        Node* temp = graph->adjList[i];
        while (temp) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    Graph graph;
    initGraph(&graph);
    generateRandomGraph(&graph);
    printGraph(&graph);
    return 0;
}
