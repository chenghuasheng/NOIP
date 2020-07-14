//P2341 [USACO03FALL][HAOI2006]受欢迎的牛 G
#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
using namespace std;
const int MAXN=10010;
const int MAXM=50010;
struct Edge{
    int from,to;
};
Edge edges[MAXM+1];
vector<int> G[MAXN+1],GNew[MAXN+1];
stack<int> st;
bool inStack[MAXN+1];
int scc[MAXN+1];
int sccIndex;
int no;
int sccNodeNum[MAXN+1];
int dfn[MAXN+1],low[MAXN+1];
int rudu[MAXN+1];
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
        int count=0;
        while(1){
            int v=st.top();
            st.pop();
            scc[v]=sccIndex;
            inStack[v]=false;
            count++;
            if (v==u) break;
        }
        sccNodeNum[sccIndex]=count;
    }
}
int n,m;
int liked[MAXN+1];
bool visited[MAXN+1];
//必须dfs进行计算，因为新图虽然没有环，但一个结点可能会有多个父结点，这样就无法树型动态规划
void dfs(int u,int r){
    liked[r]++;
    visited[u]=true;
    for(int k=0;k<GNew[u].size();k++){
        int v=GNew[u][k];
        if (!visited[v]) dfs(v,r);
    }
}

int main(){
    cin>>n>>m;
    for(int k=0;k<m;k++){
        int u,v;
        cin>>u>>v;
        G[v].push_back(u);//逆向图
        edges[k]={v,u};
    }
    for(int u=1;u<=n;u++) if (!dfn[u]) tarjan(u);
    for(int k=0;k<m;k++){
        int u=edges[k].from;
        int v=edges[k].to;
        if (scc[u]!=scc[v]){
            GNew[scc[u]].push_back(scc[v]);
            rudu[scc[v]]++;
        }
    }
    int ans=0;
    for(int u=1;u<=sccIndex;u++){
        if (rudu[u]==0){
            memset(visited,false,sizeof(visited));
            dfs(u,u);
            if (liked[u]==sccIndex) ans+=sccNodeNum[u];
        }
    }
    cout<<ans;
}