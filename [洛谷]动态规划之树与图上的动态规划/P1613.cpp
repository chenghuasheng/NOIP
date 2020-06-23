#include <iostream>
#include <climits>
#include <cstring>

using namespace std;
const int MAXN=50;
int n,m;
bool can[MAXN+1][MAXN+1][64];//can[i][j][k]表示i到j是否有一条2^k次幂的路径
int dis[MAXN+1][MAXN+1];

int main(){
    cin>>n>>m;
    memset(dis,10,sizeof(dis));
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        dis[u][v]=1;
        can[u][v][0]=true;
    }

    for(int k=1;k<=64;k++)
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            for(int o=1;o<=n;o++)
                    if (can[i][o][k-1]&&can[o][j][k-1]) {
                        can[i][j][k]=true;
                        dis[i][j]=1;
                    }
    //floyd求最短路径
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if (dis[i][k]+dis[k][j]<dis[i][j]) dis[i][j]=dis[i][k]+dis[k][j];
    cout<<dis[1][n];
}
