#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Structure for a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure for the adjacency list
struct AdjList {
    struct Node* head;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};

// Function to create a new graph with a given number of vertices
struct Graph* createGraph(int numVertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = numVertices;
    graph->array = (struct AdjList*)malloc(numVertices * sizeof(struct AdjList));

    int i;
    for (i = 0; i < numVertices; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = dest;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// Recursive function to perform topological sorting using DFS
void topologicalSortDFSUtil(struct Graph* graph, int vertex, int visited[], int stack[]) {
    visited[vertex] = 1;

    struct Node* temp = graph->array[vertex].head;
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            topologicalSortDFSUtil(graph, adjVertex, visited, stack);
        }
        temp = temp->next;
    }

    // Push the vertex to the stack after visiting all its adjacent vertices
    stack[vertex] = 1;
}

// Function to perform topological sorting using DFS
void topologicalSortDFS(struct Graph* graph) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES] = {0};
    int i;

    for (i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            topologicalSortDFSUtil(graph, i, visited, stack);
        }
    }

    // Print the vertices in the topological order
    printf("Topological Sorting: ");
    for (i = graph->numVertices - 1; i >= 0; i--) {
        if (stack[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    int numVertices = 6;
    struct Graph* graph = createGraph(numVertices);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSortDFS(graph);

    return 0;
}
