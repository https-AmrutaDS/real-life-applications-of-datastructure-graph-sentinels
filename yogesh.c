#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX 100  // Maximum number of cities

// Function to find the minimum distance vertex that has not been visited
int minDistance(int dist[], bool visited[], int n) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < n; v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Dijkstra's algorithm to find the shortest path from source to all vertices
void dijkstra(int graph[MAX][MAX], int n, int src) {
    int dist[MAX]; // dist[i] will hold the shortest distance from src to i
    bool visited[MAX]; // visited[i] will be true if vertex i is included in shortest path tree

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < n - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, visited, n);

        // Mark the picked vertex as processed
        visited[u] = true;

        // Update dist[] value of the adjacent vertices of the picked vertex
        for (int v = 0; v < n; v++)
            // Update dist[v] only if it's not visited, there's an edge from u to v,
            // and the total distance through u is smaller than the current distance
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printf("City\tDistance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\n", i, dist[i]);
}

int main() {
    int n, src;
    printf("Enter the number of cities: ");
    scanf("%d", &n);

    int graph[MAX][MAX];
    printf("Enter the adjacency matrix (distances between cities):\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter the source city (starting point): ");
    scanf("%d", &src);

    // Call Dijkstra's algorithm
    dijkstra(graph, n, src);

    return 0;
}