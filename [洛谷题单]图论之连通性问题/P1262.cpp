#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>

using namespace std;
const int MAXN=3000;
const int MAXR=8000;
const int MAXPAY=20000;
struct Edge{
    int u,v;
};
Edge edges[MAXR];
vector<int> G[MAXN+1];
vector<int> GNew[MAXN+1];

int money[MAXN+1],moneyNew[MAXN+1];
int n,p,r;
int dfn[MAXN+1],low[MAXN+1];
bool inStack[MAXN+1];
int no;
int scc[MAXN+1];
int sccIndex;
stack<int> st;
queue<int> qe;
int visited[MAXN+1];
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
        int pay=MAXPAY+1;
        while(1){
            int v=st.top();
            st.pop();
            scc[v]=sccIndex;
            if (money[v]>0&&money[v]<pay) pay=money[v];
            inStack[v]=false;
            if (v==u) break;
        }
        if (pay>MAXPAY) pay=-1;
        moneyNew[sccIndex]=pay;
    }
}
void dfs(int u){
    visited[u]=true;
    for(int k=0;k<GNew[u].size();k++){
        int v=GNew[u][k];
        dfs(v);
    }
}
int ans;
int main(){
    cin>>n;
    cin>>p;
    memset(money,-1,sizeof(money));
    memset(moneyNew,-1,sizeof(moneyNew));
    for(int i=0;i<p;i++){
        int a,b;
        cin>>a>>b;
        money[a]=b;
    }
    cin>>r;
    for(int i=0;i<r;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        edges[i]={a,b};
    }
    for(int u=1;u<=n;u++) if (!dfn[u]) tarjan(u);
    for(int i=0;i<r;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        if (scc[u]!=scc[v]){
            GNew[scc[u]].push_back(scc[v]);
            rudu[scc[v]]++;
        }
    }

    for(int u=1;u<=sccIndex;u++){
        //cout<<scc[u]<<" ";
        if (rudu[u]==0&&moneyNew[u]>0) {
            ans+=moneyNew[u];
            dfs(u);
        }
    }
    bool can=true;
    for(int u=1;u<=n;u++){//这里要使用原图的编号
        if (!visited[scc[u]]&&moneyNew[scc[u]]<0){
            can=false;
            cout<<"NO"<<endl<<u;
            break;
        }
    }
    if (can){
        cout<<"YES"<<endl<<ans;
    }
}
