#include <iostream>
#include <fstream>

using namespace std;
int e[300][300], book[300], Time[300]; // Weight, the time

int totalDistance[300][300], dis[300]; // Plugin, the distance

string res[300], Route[300][300]; // Plugin, the route

int n = 287; // n -> How many vertices the map has.
int minNum = 0, u, src, targ;

using namespace std;

void getSourceAndTarget() {
    freopen("src.in", "r", stdin);
    scanf("%d %d", &src, &targ);
    fclose(stdin);
}

void initPath() {
    // Initialize all distances as INFINITE
    // If it's the same station, it should always be zero
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0; // IF the vertices are the same, it's time is always 0
            else {
                // IF the vertices are not the same, make it's time -> [INT_MAX](Infinite Big)
                e[i][j] = INT_MAX; // init the vertices for the first time
            }
        }
    }
}

void readPath() {
    initPath();
    freopen("data.in", "r", stdin);
    int m;
    cin >> m; // count -> How many links between the basic stations
    // e.g. Line1 has 15 basic links
    for (int i = 0; i < m; i++) {
        int p, q, t, d;
        cin >> p >> q >> t >> d; // [ID1] [ID2] [time need] [distance]
        e[p][q] = e[q][p] = t; // in the same line, it should be the same time to travel both from a to b and from b to a.
        totalDistance[p][q] = totalDistance[q][p] = d;
    }
    cin >> m; // count -> How many links between the interchanges
    // e.g. Jiahewanggang has 6 links (2->3 3->2 2->14 14->2 3->14 14->3)
    for (int i = 0; i < m; i++) {
        int p, q, t, d;
        cin >> p >> q >> t >> d; // [ID1] [ID2] [time need] [distance]
        e[p][q] = t; // Different transfer time, e.g. Yantang, from 6->3 can be 1min, but from 3->6 may be longer
        totalDistance[p][q] = d;
    }
    fclose(stdin);
}

void initData() {
    for (int i = 0; i < n; i++) {
        Time[i] = e[src][i];
        dis[i] = totalDistance[src][i];
        res[i] = "";
    } // init Time, dis, res. These arrays contains the result from source to each station
}

int priceCalc(int distance) {
    return distance <= 4000 ? 2 : distance <= 12000 ? 2 + 4 * int((distance - 4) / 4) : distance <= 24000 ? 5 +
                                                                                                            int((distance -
                                                                                                                 12) /
                                                                                                                6)
                                                                                                          : 7 +
                                                                                                            int((distance -
                                                                                                                 24) /
                                                                                                                8);
    // Standard: https://zh.wikipedia.org/wiki/%E5%B9%BF%E5%B7%9E%E5%9C%B0%E9%93%81#%E7%A5%A8%E4%BB%B7
    // dis ≤ 4km: 2 CNY
    // 4km < dis ≤ 12km, every 4km in this part increase 1 CNY
    // 12km < dis ≤ 24km, every 6km in this part increase 1 CNY
    // 24km < dis, every 8km in this part increase 1 CNY
}

void printResult() {
    freopen("data.out", "w", stdout);
    cout << "NodeID\t\t\tTime\t\t\tDistance\t\t\tVia\t\t\tPrice" << endl;
    cout << targ << "\t\t\t" << Time[targ] << "\t\t\t" << dis[targ] << "\t\t\t" << res[targ] << "\t\t\t"
         << priceCalc(dis[targ]) << endl;
    fclose(stdout);
}

void dijkstra() {
    initData();
    book[src] = 1;
    for (int i = 0; i < n - 1; i++) {
        minNum = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (book[j] == 0 && Time[j] < minNum) {
                minNum = Time[j];
                u = j;
            }
        }
        book[u] = 1;
        for (int v = 0; v < n; v++) {
            if (e[u][v] < INT_MAX) {
                if (Time[v] > Time[u] + e[u][v]) {
                    Time[v] = Time[u] + e[u][v];
                    res[v] = res[u] + Route[u][v];
                    dis[v] = dis[u] + totalDistance[u][v];
                }
            }
        }
    }
    printResult();
}

int main() {
    // Read source - src and target - targ
    getSourceAndTarget();
    // Read (Import) all path
    readPath();
    // WHERE IN and WHERE OUT
    freopen("src.in", "r", stdin);
    dijkstra();
    return 0;
}