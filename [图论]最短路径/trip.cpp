//#1051. 「一本通 3.2 例 1」Sightseeing Trip
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
ifstream fin("trip.in");
ofstream fout("trip.out");
const int MAXN=100;
const int INF=0x7fffffff;

int n,m;
int w[MAXN+1][MAXN+1];
int dist[MAXN+1][MAXN+1];
int path[MAXN+1][MAXN+1];
int ans;
vector<int> circle;
void getPath(int x,int y){
    if (path[x][y]==0) return;
    int m=path[x][y];
    cout<<x<<' '<<y<<' '<<m<<endl;
    getPath(x,m);
    circle.push_back(m);
}
int main(){
    fin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if (i!=j) {
                w[i][j]=INF;
                dist[i][j]=INF;
            }
    
    for(int i=0;i<m;i++){
        int x,y,z;
        fin>>x>>y>>z;
        if (z<w[x][y]){
            w[x][y]=z;
            w[y][x]=z;
            dist[x][y]=z;
            dist[y][x]=z;
        }
    }
    ans=INF;
    for(int k=1;k<=n;k++){
        for(int i=1;i<k;i++)
            for(int j=i+1;j<k;j++)
                if ((dist[i][j]<INF)&&(w[j][k]<INF)&&(w[k][i]<INF)){
                    if (ans>dist[i][j]+w[j][k]+w[k][i]){
                        ans=dist[i][j]+w[j][k]+w[k][i];
                        cout<<i<<' '<<j<<' '<<k<<':'<<endl;
                        cout<<ans<<endl;
                        circle.clear();
                        circle.push_back(i);
                        getPath(i,j);
                        circle.push_back(j);
                        circle.push_back(k);
                    }
                }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if ((dist[i][k]<INF)&&(dist[k][j]<INF)&&(dist[i][k]+dist[k][j]<dist[i][j])){ 
                    dist[i][j]=dist[i][k]+dist[k][j];
                    path[i][j]=k;
                }    
    }
    if (ans<INF){
        for(int i=0;i<circle.size();i++) fout<<circle[i]<<' ';
    }else {
        fout<<"No solution";
    }
}
