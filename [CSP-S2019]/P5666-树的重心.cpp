#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN=299995;
struct Edge{
    int u,v;
};
int t,n;
vector<int> tree[MAXN+1];
int count[MAXN+1];
bool visited[MAXN+1];
Edge edges[MAXN];
Edge delEdge;

void dfs_calc(int u){
    visited[u]=true;
    count[u]=1;
    int s=tree[u].size();
    for(int k=0;k<s;k++){
        int v=tree[u][k];
        if ((u==delEdge.u&&v==delEdge.v)||(u==delEdge.v&&v==delEdge.u)) continue;
        if (!visited[v]){
            dfs_calc(v);
            count[u]+=count[v];
        }
    }
}
int dfs_zx(int u){
    bool hasLarge=false;
    int largeNode=0;
    int equalCount=0;
    int equalNode=0;
    int x=count[u]/2;
    int s=tree[u].size();
    for(int k=0;k<s;k++){
        int v=tree[u][k];
        if ((u==delEdge.u&&v==delEdge.v)||(u==delEdge.v&&v==delEdge.u)) continue;
        if (count[v]>x){
            hasLarge=true;
            largeNode=v;
            break;
        }else if (2*count[v]==count[u]){
            equalCount++;
            equalNode=v;
        }
    }
    if (hasLarge){
        int all=count[u];
        count[u]=all-count[largeNode];
        count[largeNode]=all;
        return dfs_zx(largeNode);
    }else if (equalCount>0){
        return u+equalNode;
    }else return u;
}
int main(){
    cin>>t;
    for(int i=0;i<t;i++){
        cin>>n;
        for(int j=1;j<=n;j++) tree[j].clear();
        for(int j=0;j<n-1;j++){
            int u,v;
            cin>>u>>v;
            tree[u].push_back(v);
            tree[v].push_back(u);
            edges[j]={u,v};
        }
        int ans=0;
        for(int j=0;j<n-1;j++){
            memset(count,0,sizeof(count));
            memset(visited,false,sizeof(visited));
            delEdge=edges[j];
            dfs_calc(delEdge.u);
            ans+=dfs_zx(delEdge.u);
            dfs_calc(delEdge.v);
            ans+=dfs_zx(delEdge.v);
        }
        cout<<ans<<endl;
    }
}
