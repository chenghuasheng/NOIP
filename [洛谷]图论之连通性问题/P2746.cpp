//P2746 [USACO5.3]校园网Network of Schools
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
const int MAXN=100;
struct Edge{
    int from,to;
};
Edge edges[MAXN*MAXN];
vector<int> G[MAXN+1];
int edgeNum;
int n;

int ans1,ans2;
int dfn[MAXN+1],low[MAXN+1];
stack<int> st;
vector<int> GNew[MAXN+1];
int scc[MAXN+1];
int sccIndex;
int no;
bool inStack[MAXN+1];
int rudu[MAXN+1],chudu[MAXN+1];

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
            scc[v]=sccIndex;
            inStack[v]=false;
            if (v==u) break;
        }
    }
}

int main(){
    cin>>n;
    for(int u=1;u<=n;u++){
        int v;
        do {
           cin>>v; 
           if (v>0) {
               G[u].push_back(v);
               edges[edgeNum]={u,v};
               edgeNum++;
           }
        }while(v>0);
    }
    for(int u=1;u<=n;u++) if (!dfn[u]) tarjan(u);
    for(int i=0;i<edgeNum;i++){
        int u=edges[i].from;
        int v=edges[i].to;
        if (scc[u]!=scc[v]){
            GNew[scc[u]].push_back(scc[v]);
            rudu[scc[v]]++;
            chudu[scc[u]]++;
        }
    }
    
    int r0=0;//入度为0的点数
    int c0=0;//出度为0的点数
    for(int u=1;u<=sccIndex;u++){
        if (rudu[u]==0) r0++;
        if (chudu[u]==0) c0++;
    }
    cout<<r0<<endl;
    if (sccIndex>1) cout<<max(r0,c0);
    else cout<<0;//如果新图只有一个点，说明本就是强连通图
}