#include <string>
//#include <fstream>
#include <iostream>

#define MAXN 99999999
#define MAX_VERTEX_NUM 300
using namespace std;

int Distance[MAX_VERTEX_NUM][MAX_VERTEX_NUM], weight[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

string link[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // The output array. link[i] will hold the node id it travel.

void initPath(int dist[MAX_VERTEX_NUM], bool sptSet[MAX_VERTEX_NUM]) {
    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
}

void readPath() {
//    ifstream fin;
//    fin.open("data.in");
    int j;
    cin >> j;
    for (int i = 0; i < j; i++) {
        int p, q, m, n;
        cin >> p >> q >> m >> n;
        weight[p][q] = m; // Input Node Weight
        Distance[p][q] = n; // Input Node Distance ( NOT WEIGHT )
    }
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < MAX_VERTEX_NUM; v++)
        if ((!sptSet[v]) && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int src) {
    cout << "Running";
    int time[MAX_VERTEX_NUM]; // The output array.  dist[i] will hold the shortest
    // distance from src to i
    int dist[MAX_VERTEX_NUM]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[MAX_VERTEX_NUM]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized
    initPath(dist, sptSet);
    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < MAX_VERTEX_NUM - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(time, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < MAX_VERTEX_NUM; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && weight[u][v] && time[u] != INT_MAX
                && dist[u] + weight[u][v] < time[v]) {
                time[v] = time[u] + weight[u][v];
                dist[v] = dist[u] + Distance[u][v];
                link[u][v] += to_string(v);
            }
    }
}

int priceCalc(int dis) {
    return dis <= 4000 ? 2 : dis <= 12000 ? 2 + 4 * int((dis - 4) / 4) : dis <= 24000 ? 5 + int((dis - 12) / 6)
                                                                                      : 7 + int((dis - 24) / 8);
    // Standard: https://zh.wikipedia.org/wiki/%E5%B9%BF%E5%B7%9E%E5%9C%B0%E9%93%81#%E7%A5%A8%E4%BB%B7
    // dis ≤ 4km: 2 CNY
    // 4km < dis ≤ 12km, every 4km in this part increase 1 CNY
    // 12km < dis ≤ 24km, every 6km in this part increase 1 CNY
    // 24km < dis, every 8km in this part increase 1 CNY
}

int main() {
    // Read (Import) all path
    readPath();
    // WHERE IN and WHERE OUT
    int src, targ;
    cin >> src >> targ;
    dijkstra(src);
    cout << weight[src][targ] << " " << Distance[src][targ] << " " << link[src][targ];
    return 0;
}