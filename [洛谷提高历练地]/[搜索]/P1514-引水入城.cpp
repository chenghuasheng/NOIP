#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
const int MAXN=500;
int n,m;
long haiba[MAXN+1][MAXN+1];
bool visited[MAXN+1][MAXN+1];
int offset[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
struct City{
    int x,y;
    long haiba;
    bool operator<(const City other) const{
        return haiba<other.haiba;
    }
};
priority_queue<City> firstRowCities;
queue<City> qe;
int overnum=0;
int ans=0;
bool firstRowVisited[MAXN+1];
bool lastRowVisited[MAXN+1];
int far[MAXN+1];
struct Region{
    int left,right;
};
Region visitedRegion[MAXN+1];

void bfs(City first){
    qe.push(first);
    visited[first.x][first.y]=true;
    while(!qe.empty()){
        City cur=qe.front();
        qe.pop();
        if (cur.x==1) firstRowVisited[cur.y]=true;
        if (cur.x==n){
            if (cur.y>visitedRegion[first.y].right) visitedRegion[first.y].right=cur.y;
            if (cur.y<visitedRegion[first.y].left) visitedRegion[first.y].left=cur.y;
            if (!lastRowVisited[cur.y]) {
                lastRowVisited[cur.y]=true;
                overnum++;
            }
        } 
        for(int k=0;k<4;k++){
            int newx=cur.x+offset[k][0];
            int newy=cur.y+offset[k][1];
            if (newx<1||newx>n||newy<1||newy>m) continue;
            if (!visited[newx][newy]&&cur.haiba>haiba[newx][newy]){
                visited[newx][newy]=true;
                City next={newx,newy,haiba[newx][newy]};
                qe.push(next);
                
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            cin>>haiba[i][j];
            if (i==1){
                City cur={i,j,haiba[i][j]};
                firstRowCities.push(cur);
            }
        }
    for(int j=1;j<=m;j++) {
        visitedRegion[j].left=m;
        visitedRegion[j].right=1;
    }
    while(!firstRowCities.empty()){
        City cur=firstRowCities.top();
        firstRowCities.pop();
        if (!firstRowVisited[cur.y]) {
            memset(visited,false,sizeof(visited));
            bfs(cur);
            if (overnum>=m){
                break;
            }
        }
    }
    if (overnum<m){
        cout<<0<<endl;
        cout<<m-overnum;
    }else {
        for(int j=1;j<=m;j++){
            if (visitedRegion[j].right>far[visitedRegion[j].left]){
               far[visitedRegion[j].left]=visitedRegion[j].right;
            }
        }
        int start=0;
        int lastStart=0;
        int end=0;
        while(end<m){
            for(int left=lastStart+1;left<=start+1;left++){
                end=max(end,far[left]);
            }
            ans++;
            lastStart=start;
            start=end;
        }
        cout<<1<<endl;
        cout<<ans;
    }
}