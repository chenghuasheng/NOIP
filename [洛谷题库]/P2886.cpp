#include <iostream>
#include <vector>
#include <map>
using namespace std;
const int MAXT=100;
const int MAXINT=1000000000;
struct Edge{
    int v,w;
};
vector<Edge> G[MAXT+10];
int dist[2][MAXT+10];
map<int,int> id;
int N,T,S,E;
int main(){
    cin>>N>>T>>S>>E;
    int cnt=1;
    id[S]=cnt++;
    id[E]=cnt++;

    for(int i=0;i<T;i++){
        int w,u,v;
        cin>>w>>u>>v;
        if (id.find(u)==id.end()) id[u]=cnt++;
        if (id.find(v)==id.end()) id[v]=cnt++;
        G[id[u]].push_back({id[v],w});
        G[id[v]].push_back({id[u],w});
    }
    for(int i=1;i<=cnt;i++){
        dist[0][i]=MAXINT;
        dist[1][i]=MAXINT;
    }
    int u=id[S];
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k].v;
        int w=G[u][k].w;
        dist[0][v]=w;
    }
    int cur=1;
    for(int i=2;i<=N;i++){
        for(int u=1;u<=cnt;u++) dist[cur][u]=MAXINT;
        for(int u=1;u<=cnt;u++){
            if (dist[!cur][u]<MAXINT){
                for(int k=0;k<G[u].size();k++){
                    int v=G[u][k].v;
                    int w=G[u][k].w;
                    dist[cur][v]=min(dist[cur][v],dist[!cur][u]+w);
                }
            }
        }
        cur=!cur;
    }
    cout<<dist[!cur][id[E]]<<endl;
}