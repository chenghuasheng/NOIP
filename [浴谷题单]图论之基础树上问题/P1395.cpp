//P1395 会议
#include <iostream>
#include <vector>
#include <climits>
using namespace std;
const int MAXN=50000;
vector<int> G[MAXN+1];
int size[MAXN+1];//指定根后，表示以i为根的子树下共有多少个节点
int dp_sum[MAXN+1];//表示以i为根时，整个树中其他节点到i的距离之和
//选定根节点后，第一次树型DP，计算出size[i]和dp_sum[根节点]，这里的根节点一般选1
void dfs(int u,int fa){
    size[u]=1;
    dp_sum[u]=0;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
            dfs(v,u);
            size[u]+=size[v];
            dp_sum[u]+=dp_sum[v]+size[v];
        }
    }
}
//第二次树形DP，计算出dp_sum[i]
void dfs1(int u,int fa,int root){
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
            dp_sum[v]=dp_sum[u]-size[v]+(size[root]-size[v]);
            dfs1(v,u,root);
        }
    }
}
int n;
int main(){
    cin>>n;
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1,0);
    dfs1(1,0,1);
    int ans=INT_MAX;
    int node=0;
    for(int u=1;u<=n;u++){
        if (ans>dp_sum[u]){
            ans=dp_sum[u];
            node=u;
        }
    }
    cout<<node<<' '<<ans;
    system("pause");
}