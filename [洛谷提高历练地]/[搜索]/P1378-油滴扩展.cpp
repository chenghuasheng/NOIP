#include <iostream>
#include <cmath>
using namespace std;
const int MAXN=10;
const double pi=3.1415926;
struct Point{
    int x,y;
    double dis_to(Point other){
        return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
    }
};

Point points[MAXN];
double dis[MAXN][MAXN];
double dis_edge[MAXN][4];
int minx,maxx,miny,maxy;
double maxarea;
double r[MAXN];
bool used[MAXN];
int n;
double get_r(int k){
    double minv=dis_edge[k][0];
    for(int i=1;i<4;i++) minv=min(minv,dis_edge[k][i]);
    for(int i=0;i<n;i++)
        if (i!=k&&used[i]) minv=min(minv,max(dis[k][i]-r[i],0.0));//没有放油滴的点是可以漫过去的
    return minv;
}
void dfs(int i,double areasum){
   if (i>=n) {
       maxarea=max(maxarea,areasum);
   }else {
        for(int k=0;k<n;k++){
                if (used[k]) continue;
                double cur_r=get_r(k);
                double cur_s=pi*cur_r*cur_r;
                r[k]=cur_r;
                used[k]=true;
                dfs(i+1,areasum+cur_s);
                r[k]=0;
                used[k]=false;
        }
   }
}
double area_ju;
int main(){
    cin>>n;
    Point a,b;
    cin>>a.x>>a.y;
    cin>>b.x>>b.y;
    minx=min(a.x,b.x);
    maxx=max(a.x,b.x);
    miny=min(a.y,b.y);
    maxy=max(a.y,b.y);
    area_ju=abs(a.x-b.x)*abs(a.y-b.y);
    for(int i=0;i<n;i++){
        cin>>points[i].x>>points[i].y;
        dis_edge[i][0]=abs(points[i].x-minx);
        dis_edge[i][1]=abs(points[i].x-maxx);
        dis_edge[i][2]=abs(points[i].y-miny);
        dis_edge[i][3]=abs(points[i].y-maxy);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
        if (i!=j){
            dis[i][j]=points[i].dis_to(points[j]);
        }
    }
    dfs(0,0);
    cout<<int(area_ju-maxarea+0.5);
}

