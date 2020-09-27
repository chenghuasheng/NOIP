#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAXN=210;
const int MAXQ=50000;
const int INF=0x3fffffff;

int n,m,q;
int bt[MAXN];
int dist[MAXN][MAXN];
//对floyd算法进行改造，每次通过当前已重建的村庄u进行松弛操作
void update(int u){
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dist[i][j]=dist[j][i]=min(dist[i][j],dist[i][u]+dist[u][j]);
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<n;i++) scanf("%d",&bt[i]);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            dist[i][j]=INF;
    for(int k=0;k<m;k++){
        int u,v,w;
        scanf("%d %d %d",&u,&v,&w);
        dist[u][v]=dist[v][u]=w;
    }
    scanf("%d",&q);
    int now=0;
    for(int k=0;k<q;k++){
        int x,y,t;
        scanf("%d %d %d",&x,&y,&t);
        if (bt[x]>t||bt[y]>t) printf("%d\n",-1);
        else {
            while(bt[now]<=t&&now<n){
                update(now);
                now++;
            }
            if (dist[x][y]==INF) printf("%d\n",-1);
            else printf("%d\n",dist[x][y]);
        }
    }
}
