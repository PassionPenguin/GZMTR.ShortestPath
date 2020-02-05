// A C++ program for Dijkstra's single source shortest path algorithm.
// The program is for adjacency matrix representation of the graph

#include <limits.h>
#include <fstream>

// Number of vertices in the graph
#define V 400

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
long long minDistance(long long dist[], bool sptSet[]) {
    // Initialize min value
    long long min = INT_MAX, min_index;

    for (long long v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(long long dist[]) {
    printf("Vertex \t\t Distance from Source\n");
    for (long long i = 0; i < V; i++)
        printf("%lld \t\t %lld\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(long long graph[V][V], long long src) {
    long long dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (long long i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (long long count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        long long u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (long long v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // prlong long the constructed distance array
    printSolution(dist);
}

// driver program to test above function
int main() {
    /* Let us create the example graph discussed above */
    freopen("data.in", "r",stdin);
//    long long graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
//                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
//                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
//                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
//                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
//                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
//                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
//                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
//                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    long long graph[V][V];
    long long n;
    scanf("%lld", &n);
    for (long long i = 0; i < n; i++) {
        long long p, q, k, j;
        scanf("%lld %lld %lld %lld", &p, &q, &k, &j);
        graph[p][q] = graph[q][p] = k;
    }

    dijkstra(graph, 0);

    return 0;
}