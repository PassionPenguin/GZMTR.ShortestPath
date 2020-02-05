#include <iostream>
#include <fstream>

using namespace std;
int e[300][300], book[300], Time[300];
long long totalDistance[300][300], dis[300];
string res[300], Route[300][300];
int n = 290, m;
int minNum = 0, u, src;

using namespace std;

void initPath() {
    // Initialize all distances as INFINITE
    // If it's the same station, it should always be zero
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0;
            else {
                e[i][j] = INT_MAX;
            }
        }
    }
}

void readPath() {
    freopen("data.in", "r", stdin);
    cin >> m;
    for (int i = 0; i < m; i++) {
        int p, q, t, d;
        cin >> p >> q >> t >> d;
        e[p][q] = e[q][p] = t;
        totalDistance[p][q] = totalDistance[q][p] = d;
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int p, q, t, d;
        cin >> p >> q >> t >> d;
        e[p][q] = t;
        totalDistance[p][q] = d;
    }
    fclose(stdin);
}

void initData() {
    for (int i = 0; i < n; i++) {
        Time[i] = e[src][i];
        dis[i] = totalDistance[src][i];
        res[i] = "";
    }
    book[src] = 1;
}

void dijkstra() {
    initData();
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
    for (int i = 1; i <= n; i++) {
        cout << i << "\t\t\t" << Time[i] << "\t\t\t" << dis[i] << "\t\t\t" << res[i] << "\t\t\t" << priceCalc(dis[i])
             << endl;
    }
    fclose(stdout);
}

int main() {
    // Read (Import) all path
    readPath();
    // WHERE IN and WHERE OUT
    freopen("src.in", "r", stdin);
    src=140;
    dijkstra();
    printResult();
    return 0;
}