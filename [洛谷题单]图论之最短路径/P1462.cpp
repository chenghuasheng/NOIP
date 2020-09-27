#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
const int MAXN=10000;
const int INF=1000000001;
int n,m,b;
int f[MAXN+1];
struct Edge{
    int v,w;
};
vector<Edge> G[MAXN+1];
int minf=INF;
int maxf=0;
bool disabled[MAXN+1];
int dist[MAXN+1];
queue<int> qu;
void spfa(int root){
    if (disabled[root]) return;
    dist[root]=0;
    qu.push(root);
    while(!qu.empty()){
        int u=qu.front();
        qu.pop();
        for(int k=0;k<G[u].size();k++){
            int v=G[u][k].v;
            int w=G[u][k].w;
            if (!disabled[v]&&dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                qu.push(v);
            }
        }
    }
}

int main(){
    cin>>n>>m>>b;
    for(int i=1;i<=n;i++) {
        cin>>f[i];
        minf=min(minf,f[i]);
        maxf=max(maxf,f[i]);
    }
    for(int k=0;k<m;k++){
        int a,b,c;
        cin>>a>>b>>c;
        G[a].push_back({b,c});
        G[b].push_back({a,c});
    }
    int left=minf;
    int right=maxf;
    while(left<right){
        int mid=(left+right)/2;
        memset(disabled,false,sizeof(disabled));
        for(int i=1;i<=n;i++){
            if (f[i]>mid) disabled[i]=true;
            dist[i]=INF;
        }
        spfa(1);
        if (dist[n]>b){
            left=mid+1;
        }else right=mid;
    }
    memset(disabled,false,sizeof(disabled));
    for(int i=1;i<=n;i++){
        if (f[i]>right) disabled[i]=true;
        dist[i]=INF;
    }
    spfa(1);
    if (dist[n]<=b) cout<<right;
    else cout<<"AFK";
}