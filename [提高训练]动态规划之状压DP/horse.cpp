#include<fstream>
#include<vector>
#include<iostream>

using namespace std;
ifstream fin("horse.in");
ofstream fout("horse.out");

const int MAXN=10;
const int MAXS=1023;
long long dp[MAXN+1][MAXN*MAXN+1][MAXS+1];//dp[i][j][s]前i行格子放置j个国王最后一行（即第i行）状态为s时的方案数
int num1[MAXS+1];//保存可行状态中1的个数
vector<int> states;//保存一行内可行的状态，将不可行的状态去掉了，这就是状态压缩

int n,k;
long long ans;
int check_count(int s) {
    if (s&(s<<1)) return -1;
    int k=0;
    while(s>0){
        k+=(s&1);
        s=s>>1;
    }
    return k;
}

int main(){
    fin>>n>>k;
    //将可行状态保存，并记录对应状态1的个数
    for(int state=0;state<=(1 << n) - 1;state++) {
        int t=check_count(state);
        if (t>=0) {
            states.push_back(state);
            num1[state]=t;
        }
    }
    int statecount=states.size();
    //进行动规
    for(int i=0;i<=n;i++) dp[i][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int w=1;w<=k;w++){
            if (w>n*i) break;
            for(int i1=0;i1<statecount;i1++)
                for(int i2=0;i2<statecount;i2++)  {
                    int s1=states[i1];
                    int s2=states[i2];
                    if ((s1&s2)||(s1>>1&s2)||(s1<<1&s2)) continue;//上下两行状态是否可行
                    int u=num1[s1];
                    if (u<=w) {
                        dp[i][w][s1]+=dp[i-1][w-u][s2];
                    }
                }
        }
    }
    //统计最终答案
    ans=0;
    for(int i=0;i<statecount;i++){
        int s=states[i];
        ans+=dp[n][k][s];
    }
    fout<<ans;
}