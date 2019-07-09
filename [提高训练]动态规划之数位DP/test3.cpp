//#1022. 「一本通 5.3 练习 3」恨 7 不成妻
#include <fstream>
#include <cmath>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

const int MAXL = 18;
const long long LIMIT = 1000000007;
long long c[MAXL + 1][10][7][7];//c[i][j][u][v] 表示高度为i的且以j为根结点，由根结点到叶结点的路径所经过的数字组成一个数，
                                //在这些数中不含数字7且数字之和对7取余为u,数对7取余为v的所有数的个数
long long f[MAXL + 1][10][7][7];//同上，是所有数的和
long long g[MAXL + 1][10][7][7];//同上，是所有数的平方和
long long mi[MAXL];

long long safemulti(long long num1,long long num2){
    num1=num1 % LIMIT;
    num2=num2 % LIMIT;
    return (num1 * num2) % LIMIT;
}
void dp() {
    for (int i = 0; i <= 9; i++)
        if (i != 7) {
            c[0][i][i % 7][i % 7] = 1;
            f[0][i][i % 7][i % 7] = i;
            g[0][i][i % 7][i % 7] = i * i;
        }

    for (int i = 1; i <= MAXL; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 7)
                continue;
            for (int k = 0; k <= 9; k++) {
                if (k == 7)
                    continue;
                for (int u = 0; u < 7; u++)
                    for (int v = 0; v < 7; v++) {
                        if (c[i - 1][k][u][v] > 0) {
                            int r1 = (j + u) % 7;
                            int r2 = (j * (mi[i] % 7) + v) % 7;
                            c[i][j][r1][r2] += c[i - 1][k][u][v];
                            long long n0=safemulti(j*mi[i],c[i - 1][k][u][v]);
                            f[i][j][r1][r2] = (f[i][j][r1][r2] + n0 + f[i - 1][k][u][v]) % LIMIT;
                            long long n1=safemulti(safemulti(j*mi[i],j*mi[i]),c[i - 1][k][u][v]);
                            long long n2=safemulti(2*j*mi[i], f[i - 1][k][u][v]);
                            g[i][j][r1][r2] = (g[i][j][r1][r2] + n1 + n2 + g[i - 1][k][u][v]) % LIMIT;
                        }
                    }
            }
        }
    }
}

long long calc(long long x) {
    int t[MAXL + 1] = { 0 };
    int k = 0;
    while (x > 0) {
        int d = x % 10;
        t[k] = d;
        k++;
        x = x / 10;
    }
    long long ans = 0, tot1 = 0, tot2 = 0, tot3 = 0;
    int i = max(k - 1, 0);
    for (; i >= 0; i--) {
        int d = t[i];
        for (int j = 0; j < d; j++) {
            for (int u = 0; u < 7; u++)
                for (int v = 0; v < 7; v++) {
                    int r1 = (tot1 + u) % 7;
                    int r2 = (tot2 * (mi[i + 1] % 7) + v) % 7;
                    if (r1 != 0 && r2 != 0 && c[i][j][u][v] > 0) {
                        long long n1=safemulti(safemulti(tot3*mi[i+1],tot3*mi[i+1]),c[i][j][u][v]);
                        long long n2=safemulti(2*tot3*mi[i+1],f[i][j][u][v]);
                        ans = (ans + n1 + n2 + g[i][j][u][v]) % LIMIT;
                    }
                }
        }
        if (d == 7)
            break;
        tot1 = (tot1 + d) % 7;
        tot2 = (tot2 * 10 + d) % 7;
        tot3 = (tot3 * 10 + d);
        if (i == 0 && tot1 != 0 && tot2 != 0)
            ans = (ans + safemulti(tot3,tot3)) % LIMIT;
    }
    return ans;
}

long long t, l, r;
int main() {
    mi[0] = 1;
    for (int i = 1; i <= MAXL; i++) mi[i] = mi[i - 1] * 10;
    dp();
    fin >> t;
    for (int i = 0; i < t; i++) {
        fin >> l >> r;
        long long n1 = calc(l - 1);
        long long n2 = calc(r);
        fout << (n2 - n1 + LIMIT) % LIMIT << endl;
    }
}