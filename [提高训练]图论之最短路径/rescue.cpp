//#1052. 「一本通 3.2 例 2」拯救大兵瑞恩
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
ifstream fin("rescue.in");
ofstream fout("rescue.out");

const int MAXN = 10;
const int MAXL = 1024;
struct edge {
    int l, x, y;
    int w;
};

vector<edge> graph[MAXL][MAXN + 1][MAXN + 1];//建立2的p次幂层，钥匙为i的对应2的（i-1)次幂层。
                //如果既有1钥匙和2钥匙，则对应层次为2^(1-1)+2^(2-1)=3。
int walldoor[MAXN + 1][MAXN + 1][MAXN + 1][MAXN + 1];
int off[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
int key[MAXN + 1][MAXN + 1];
int n, m, p;
int levelnum;
void build_graph() {
    for (int x1 = 1; x1 <= n; x1++) {
        for (int y1 = 1; y1 <= m; y1++) {
            for (int d = 0; d < 4; d++) {
                int x2 = x1 + off[d][0];
                int y2 = y1 + off[d][1];
                if (x2 < 1 || x2 > n || y2 < 1 || y2 > m)
                    continue;
                if (walldoor[x1][y1][x2][y2] == -1) {
                    for (int l = 0; l < levelnum; l++) graph[l][x1][y1].push_back({ l, x2, y2, 1 });
                } else if (walldoor[x1][y1][x2][y2] > 0) {
                    int flag = 1 << (walldoor[x1][y1][x2][y2] - 1);
                    for (int l = 1; l < levelnum; l++)
                        if (l & flag)
                            graph[l][x1][y1].push_back({ l, x2, y2, 1 });
                }
            }
            if (key[x1][y1] > 0) {
                for (int l = 0; l < levelnum; l++)
                    if (l != key[x1][y1]) graph[l][x1][y1].push_back({ l|key[x1][y1], x1, y1, 0 });               
            }
        }
    }
}
int dist[MAXL][MAXN + 1][MAXN + 1];
bool in[MAXL][MAXN + 1][MAXN + 1];
struct node {
    int l, x, y;
};
queue<node> q;

void spfa() {
    for (int l = 0; l < levelnum; l++)
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= m; y++) dist[l][x][y] = 1000;
    dist[0][1][1] = 0;
    q.push({ 0, 1, 1});
    in[0][1][1] = true;
    while (!q.empty()) {
        node cur = q.front();
        q.pop();
        in[cur.l][cur.x][cur.y] = false;
        int s = graph[cur.l][cur.x][cur.y].size();
        for (int k = 0; k < s; k++) {
            edge e = graph[cur.l][cur.x][cur.y][k];
            int t = dist[cur.l][cur.x][cur.y] + e.w;
            if (t < dist[e.l][e.x][e.y]) {
                dist[e.l][e.x][e.y] = t;
                if (!in[e.l][e.x][e.y]) {
                    q.push({ e.l, e.x, e.y });
                    in[e.l][e.x][e.y] = true;
                }
            }
        }
    }
}
int main() {
    fin >> n >> m >> p;
    memset(walldoor, -1, sizeof(walldoor));
    int k;
    fin >> k;
    for (int i = 0; i < k; i++) {
        int x1, y1, x2, y2, g;
        fin >> x1 >> y1 >> x2 >> y2 >> g;
        walldoor[x1][y1][x2][y2] = g;
        walldoor[x2][y2][x1][y1] = g;
    }

    int s;
    fin >> s;
    for (int i = 0; i < s; i++) {
        int x, y, q;
        fin >> x >> y >> q;
        key[x][y] += 1 << (q - 1);//将钥匙转化为对应的层次，可累加
    }
    levelnum = 1 << p;
    build_graph();
    spfa();
    int ans = 1000;
    for (int l = 0; l < levelnum; l++)
        if (dist[l][n][m] < ans)
            ans = dist[l][n][m];
    if (ans == 1000)
        fout << -1;
    else
        fout << ans;
}