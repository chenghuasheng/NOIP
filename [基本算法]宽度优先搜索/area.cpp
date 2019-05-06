#include <fstream>
#include <queue>
using namespace std;
ifstream fin("area.in");
ofstream fout("area.out");

struct Point{
    int x,y;
};
int dir_off[4][2]={{-1,0},{1,0},{0,-1},{0,1}};

const int MAXN=100;
int colors[MAXN][MAXN];
int n,m;
int ans;

int bfs(int x,int y){
    if (colors[x][y]==0) return 0;
    int c=0;
    queue<Point> qe;
    Point start={x,y};
    qe.push(start);
    c++;
    colors[x][y]=0;

    while(!qe.empty()){
        Point cur=qe.front();
        for(int d=0;d<4;d++){
            int newx=cur.x+dir_off[d][0];
            int newy=cur.y+dir_off[d][1];
            if (newx<0||newx>=n||newy<0||newy>=m) continue;
            if (colors[newx][newy]==1){
                Point next={newx,newy};
                qe.push(next);
                c++;
                colors[newx][newy]=0;
            }
        }
        qe.pop();
    }
    return c;
}
int main(){
    fin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) fin>>colors[i][j];

    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if (colors[i][j]==1) {
                    int area=bfs(i,j);
                    if (area>ans) ans=area;
            }
    fout<<ans;
}