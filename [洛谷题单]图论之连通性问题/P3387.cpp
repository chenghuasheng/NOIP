#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int MAXN=10000;
const int MAXM=100000;

struct Edge{
    int u,v;
};
Edge edges[MAXM];
int ecount;

int w[MAXN+1];
vector<int> G[MAXN+1],GNew[MAXN+1];
int n,m;
int no;
int dfn[MAXN+1],low[MAXN+1];
int sccIndex;
int scc[MAXN+1];
int sccw[MAXN+1];
stack<int> st;
bool inStack[MAXN+1];

void tarjan(int u){
    dfn[u]=low[u]=++no;
    st.push(u);
    inStack[u]=true;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (inStack[v]){
            low[u]=min(low[u],dfn[v]);
        }else if (!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
    }
    if (dfn[u]==low[u]){
        sccIndex++;
        while(1){
            int v=st.top();
            st.pop();
            inStack[v]=false;
            scc[v]=sccIndex;
            sccw[sccIndex]+=w[v];
            if (v==u) break;
        }
    }
}
int maxw[MAXN+1];
bool visited[MAXN+1];

void dp(int u){
    maxw[u]=sccw[u];
    visited[u]=true;
    for(int k=0;k<GNew[u].size();k++){
        int v=GNew[u][k];
        if (!visited[v]) dp(v);
        maxw[u]=max(maxw[u],maxw[v]+sccw[u]);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        edges[ecount++]={u,v};
    }
    for(int u=1;u<=n;u++) if (!dfn[u]) tarjan(u);
    for(int i=0;i<ecount;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        if (scc[u]!=scc[v]){
            GNew[scc[u]].push_back(scc[v]);
        }
    }
    for(int u=1;u<=sccIndex;u++) if (!visited[u]) dp(u);
    int ans=0;
    for(int u=1;u<=sccIndex;u++){
        ans=max(ans,maxw[u]);
    }
    cout<<ans;
}
