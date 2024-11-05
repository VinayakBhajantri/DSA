#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100


struct Node {
    int vertex;
    struct Node* next;
};


struct AdjList {
    struct Node* head;
};

// Structure for the graph
struct Graph {
    int numVertices;
    struct AdjList* array;
};


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

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = src;
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}


int BFS(struct Graph* graph, int src) {
    int visited[MAX_VERTICES] = {0};
    int distance[MAX_VERTICES] = {0};

    // Mark the source vertex as visited
    visited[src] = 1;

    // Create a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    // Enqueue the source vertex
    queue[rear++] = src;

    while (front != rear) {
        // Dequeue a vertex from the queue
        int currentVertex = queue[front++];

        struct Node* temp = graph->array[currentVertex].head;
        while (temp != NULL) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                // Mark the adjacent vertex as visited
                visited[adjVertex] = 1;

                // Set the distance of the adjacent vertex
                distance[adjVertex] = distance[currentVertex] + 1;

                // Enqueue the adjacent vertex
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }

    // Find the vertex with maximum distance
    int maxDistance = 0;
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        if (distance[i] > distance[maxDistance]) {
            maxDistance = i;
        }
    }

    return maxDistance;
}

// Function to find the diameter of the tree or graph
int findDiameter(struct Graph* graph) {

    int vertex1 = BFS(graph, 0);

    // Find the farthest vertex from vertex1 using BFS
    int vertex2 = BFS(graph, vertex1);

    return BFS(graph, vertex2);
}

int main() {
    int numVertices = 6;
    struct Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    int diameter = findDiameter(graph);
    printf("Diameter of the tree/graph: %d\n", diameter);

    return 0;
}

