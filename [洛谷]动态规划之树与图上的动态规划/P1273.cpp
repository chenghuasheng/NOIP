#include <iostream>
#include <vector>
#include <climits>

using namespace std;
const int MAXN=3000;
struct Edge{
    int to;
    int cost;
};
vector<Edge> G[MAXN+1];
int dp_profit[MAXN+1][MAXN+1];//dp_profit[u][i]表示以u为根结点的子树下，使i个终端用户收看的最大利润
int dp_maxUser[MAXN+1];
int n,m;
int pay[MAXN+1];
void dp(int u){
    dp_profit[u][0]=0;
    dp_maxUser[u]=0;
    if (u>n-m) {
        dp_profit[u][1]=pay[u];
        dp_maxUser[u]=1;
    }
    else {
        int s=G[u].size();
        for(int k=0;k<s;k++){
            int v=G[u][k].to;
            dp(v);
            int newMaxUser=dp_maxUser[u]+dp_maxUser[v];
            for(int i=newMaxUser;i>0;i--){
                for(int j=1;j<=dp_maxUser[v];j++){
                  if (i-j>=0&&i-j<=dp_maxUser[u]) {
                      dp_profit[u][i]=max(dp_profit[u][i],dp_profit[v][j]+dp_profit[u][i-j]-G[u][k].cost);
                  }
                }
            }
            dp_maxUser[u]=newMaxUser;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int u=1;u<=n-m;u++){
        int k;
        cin>>k;
        for(int j=1;j<=k;j++){
            int a,c;
            cin>>a>>c;
            G[u].push_back({a,c});
        }
    }
    for(int u=n-m+1;u<=n;u++) cin>>pay[u];
    for(int u=1;u<=n;u++) for(int i=0;i<=m;i++) dp_profit[u][i]=INT_MIN;
    dp(1);
    int ans=0;
    for(int i=m;i>=0;i--) {
        if (dp_profit[1][i]>=0) {
            ans=i;
            break;
        }
    }
    cout<<ans;
}