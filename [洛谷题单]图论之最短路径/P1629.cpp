#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
const int MAXN=1000;
const int INF=0x3fffffff;
int n,m;
int dist[MAXN+1];
int dist1[MAXN+1];
struct Edge{
    int v,w;
};
vector<Edge> G[MAXN+1],G1[MAXN+1];
queue<int> qu;
//正向图上spfa()
void spfa(int root){
    for(int i=1;i<=n;i++) dist[i]=INF;
    dist[1]=0;
    qu.push(root);
    while(!qu.empty()){
        int u=qu.front();
        qu.pop();
        for(int k=0;k<G[u].size();k++){
            int v=G[u][k].v;
            int w=G[u][k].w;
            if (dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                qu.push(v);
            }
        }
    }
}
//逆向图上spfa()
void spfa1(int root){
    for(int i=1;i<=n;i++) dist1[i]=INF;
    dist1[1]=0;
    qu.push(root);
    while(!qu.empty()){
        int u=qu.front();
        qu.pop();
        for(int k=0;k<G1[u].size();k++){
            int v=G1[u][k].v;
            int w=G1[u][k].w;
            if (dist1[u]+w<dist1[v]){
                dist1[v]=dist1[u]+w;
                qu.push(v);
            }
        }
    }
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        G[u].push_back({v,w});
        G1[v].push_back({u,w});
    }
    spfa(1);
    spfa1(1);
    int ans=0;
    for(int i=1;i<=n;i++) ans+=dist[i]+dist1[i];
    printf("%d",ans);
}