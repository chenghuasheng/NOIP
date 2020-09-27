#include <iostream>
#include <vector>
#include <queue>
#include <cstdio>

using namespace std;
const int MAXN=100000;
const int INF=0x3fffffff;

struct Edge{
    int v,w;
};
vector<Edge> G[MAXN+1];
int dist[MAXN+1];
struct Node{
    int u;
    bool operator<(const Node other)const{
        return dist[u]>dist[other.u];
    }
};
priority_queue<Node> pri_qu;
bool in_queue[MAXN+1];

int n,m,s;
void dijkstra(int s){
    for(int i=1;i<=n;i++) dist[i]=INF;
    dist[s]=0;
    pri_qu.push({s});
    in_queue[s]=true;
    while(!pri_qu.empty()){
        int u=pri_qu.top().u;
        pri_qu.pop();
        in_queue[u]=false;
        for(int k=0;k<G[u].size();k++){
            int v=G[u][k].v;
            int w=G[u][k].w;
            if (dist[u]+w<dist[v]){
                dist[v]=dist[u]+w;
                if (!in_queue[v]) {
                    pri_qu.push({v});
                    in_queue[v]=true;
                }
            }
        }
    }
}
int main(){
    scanf("%d %d %d",&n,&m,&s);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        G[u].push_back({v,w});
    }
    dijkstra(s);
    for(int i=1;i<=n;i++) printf("%d ",dist[i]);
}