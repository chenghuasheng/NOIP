#include <iostream>
#include <cstring>

using namespace std;
const int MAXN=10;
const int INF=-1;
int n,m;
int volunteers[MAXN][MAXN];
int graph[MAXN*MAXN][MAXN*MAXN];
int dir_off[4][2]={{0,1},{-1,0},{0,-1},{1,0}};
int mindist[MAXN*MAXN][MAXN*MAXN];

int main()
{
    cin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) cin>>volunteers[i][j];
    memset(graph,-1,sizeof(graph));
    memset(mindist,-1,sizeof(mindist));

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++){
            int no=i*m+j;
            for(int d=0;d<4;d++){
                int i1=i+dir_off[d][0];
                int j1=j+dir_off[d][1];
                if (i1>=0&&i1<n&&j1>=0&&j1<m){
                    int no1=i1*m+j1;
                    graph[no][no1]=volunteers[i1][j1];
                    graph[no1][no]=volunteers[i][j];
                }
            }
        }
    for(int k=0;k<n*m;k++)
        for(int i=0;i<n*m;i++)
            for(int j=0;j<n*m;j++)
                if (mindist[i][k]!=-1&&graph[k][j]!=-1&&(
                    mindist[i][j]==-1||mindist[i][k]+graph[k][j]<mindist[i][j])){
                        mindist[i][j]=mindist[i][k]+graph[k][j];
                    }
    
            

}

