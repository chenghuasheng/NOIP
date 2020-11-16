#include <iostream>
#include <vector>
#include <map>
#define ll long long
using namespace std;
const int MAXN=1000000000;
const int MAXK=50011;
const int MOD=998244353;
map<int,int> id;
ll dp[2][MAXK*2];
ll dp_sum[2];
int n,m,k;
vector<int> G[MAXK*2];

int main(){
    cin>>n>>m>>k;
    id[1]=1;
    int cnt=1;
    for(int i=0;i<k;i++){
        int a,b;
        cin>>a>>b;
        if (a!=b){
            //为有限制的点编个新号，在新号上建邻接表
            if (id.find(a)==id.end()) id[a]=++cnt;
            if (id.find(b)==id.end()) id[b]=++cnt;
            G[id[b]].push_back(id[a]);
        }
    }
    //dp[cur][cnt+1]存放本轮中到达没有限制的那些点的方案数总和
    dp[0][1]=1;
    dp_sum[0]=1;
    int cur=1;
    for(int j=1;j<=m;j++){
        dp_sum[cur]=0;
        for(int i=1;i<=cnt;i++){
            dp[cur][i]=(dp_sum[!cur]+MOD-dp[!cur][i]) % MOD;
            for(int k=0;k<G[i].size();k++){
                dp[cur][i]=(dp[cur][i]+MOD-dp[!cur][G[i][k]]) % MOD;
            }
            dp_sum[cur]=(dp_sum[cur]+dp[cur][i]) % MOD;
        }
        dp[cur][cnt+1]=(((dp_sum[!cur]-dp[!cur][cnt+1])*(n-cnt))%MOD+(dp[!cur][cnt+1]*(n-cnt-1)%MOD)) % MOD;
        dp_sum[cur]=(dp_sum[cur]+dp[cur][cnt+1]) % MOD;
        cur=!cur;
    }
    cout<<dp[!cur][1]<<endl;
}