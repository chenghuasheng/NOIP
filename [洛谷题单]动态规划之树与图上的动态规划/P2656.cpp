#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;
const int MAXN=80000;
const int MAXM=200000;
int n,m,s;
struct Edge{
    int from;
    int to;
    int mogu;
    double xishu;
};
Edge edges[MAXM+1];
vector<Edge> G[MAXN+1];
vector<Edge> GNew[MAXN+1];
int nw[MAXN+1],dp[MAXN+1];

int dfn[MAXN+1],low[MAXN+1],scc[MAXN+1];
stack<int> st;
bool inStack[MAXN+1];
int index,sccIndex;

void tarjan(int u){
    dfn[u]=low[u]=index++;
    st.push(u);
    inStack[u]=true;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k].to;
        if (inStack[v]){
            low[u]=min(low[u],dfn[v]);
        }else if (!dfn[v]){
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
    }
    if (dfn[u]==low[u]){
        sccIndex++;
        while(!st.empty()){
            int v=st.top();
            st.pop();
            inStack[v]=false;
            scc[v]=sccIndex;
            if (v==u) break;
        } 
    }
}
void buildGNew(){
    for(int i=0;i<m;i++){
        int u=edges[i].from;
        int v=edges[i].to;
        if (scc[u]==0) continue;
        if (scc[u]==scc[v]){
            int sum=0;
            int t=edges[i].mogu;
            while(t>0){
                sum+=t;
                t=t*edges[i].xishu;
            }
            nw[scc[u]]+=sum;
        }else {
            GNew[scc[u]].push_back({scc[u],scc[v],edges[i].mogu,edges[i].xishu});
        }
    }
}

// void spfa(){
//     queue<int> qe;
//     qe.push(s);
//     dp[s]=nw[s];
//     while(!qe.empty()){
//         int u=qe.front();
//         qe.pop();
//         for(int k=0;k<GNew[u].size();k++){
//             int v=GNew[u][k].to;
//             if (dp[v]<dp[u]+GNew[u][k].mogu+nw[v]){
//                 dp[v]=dp[u]+GNew[u][k].mogu+nw[v];
//                 qe.push(v);
//             } 
//         }
//     }
// }
bool visited[MAXN+1];
void tree(int u){
    int t=0;
    for(int k=0;k<GNew[u].size();k++){
        int v=GNew[u][k].to;
        if (!visited[v]) tree(v);
        t=max(t,GNew[u][k].mogu+dp[v]);
    }
    dp[u]=nw[u]+t;
    visited[u]=true;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,gu;
        double xi;
        cin>>u>>v>>gu>>xi;
        edges[i]={u,v,gu,xi};
        G[u].push_back(edges[i]);
    }
    cin>>s;
    tarjan(s);
    buildGNew();
    s=scc[s];
    //spfa();
    tree(s);
    // int ans=0;
    // for(int u=1;u<=sccIndex;u++) ans=max(ans,dp[u]);
    // cout<<ans;
    cout<<dp[s];
}