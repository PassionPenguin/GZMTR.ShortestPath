#include <iostream>
#include <fstream>

using namespace std;
int e[300][300], book[300], Time[300];
long long totalDistance[300][300], dis[300];
string res[300], Route[300][300];
int n = 290, m;
int minNum = 0, u, s;

int main() {
    freopen("src.in", "r", stdin);
    scanf("%d", &s);
    fclose(stdin);
    freopen("data.in", "r", stdin);
    cin >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                e[i][j] = 0;
            else {
                e[i][j] = INT_MAX;
            }
        }
    }
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
    for (int i = 0; i < n; i++) {
        Time[i] = e[s][i];
        dis[i] = totalDistance[s][i];
        res[i] = "";
    }
    book[s] = 1;
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
    freopen("data.out", "w", stdout);
    cout << "NodeID\t\t\tTime\t\t\tDistance\t\t\tVia" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << "\t\t\t" << Time[i] << "\t\t\t" << dis[i] << "\t\t\t" << res[i] << endl;
    }
    fclose(stdout);
    return 0;
}