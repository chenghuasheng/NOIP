//#1025. 「一本通 5.4 例 2」牧场的安排
#include <fstream>
#include <vector>

using namespace std;
ifstream fin("cowfood.in");
ofstream fout("cowfood.out");
const int MAXN = 12;
const int MAXS = 4096;
int m, n;
int flag[MAXN + 1];
long long dp[MAXN + 1][MAXS + 1];//dp[i][s]表示前i行中，第i行的状态为s时的方案数
vector<int> states;
long long ans;

int main() {
    fin >> m >> n;
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            fin >> a;
            flag[i] = (flag[i] << 1) + a;
        }
    }
    
    for (int s = 0; s <= (2 << n) - 1; s++) {
        if (s&(s<<1)) continue;
        states.push_back(s);
    }
    int count = states.size();
    //dp
    dp[0][0] = 1;
    for (int i = 1; i <= m; i++) {
        for (int i1 = 0; i1 < count; i1++) {
            int s1 = states[i1];
            if (((~flag[i]) & s1) > 0)
                continue;
            for (int i2 = 0; i2 < count; i2++) {
                int s2 = states[i2];
                if ((s1 & s2) > 0) continue;
                dp[i][s1] = (dp[i][s1]+dp[i - 1][s2]) % 100000000;
            }
        }
    }
    //output

    for (int i = 0; i < count; i++) {
        int s = states[i];
        ans =(ans+ dp[m][s]) % 100000000;
    }
    fout << ans;
}