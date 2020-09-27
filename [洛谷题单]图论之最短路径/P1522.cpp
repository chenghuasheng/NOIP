#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const int MAXN=150;
const int INF=0x2fffffff;
int n;
struct Coor{
    double x,y;
    double dist_to(const Coor other){
        return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
    }
};
Coor crs[MAXN+1];
double dist[MAXN+1][MAXN+1];
double maxdist[MAXN+1];

void floyd(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if (i==k||k==j||j==i) continue;
                dist[i][j]=dist[j][i]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
}
double ans=0.0;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        crs[i]={x,y};
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            char c;
            cin>>c;
            int flag=c-'0';
            if (flag==1) dist[i][j]=crs[i].dist_to(crs[j]);
            else if (i==j) dist[i][j]=0;
            else  dist[i][j]=INF;
        }
    floyd();
    ans=INF;
    double oldmax=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if (dist[i][j]!=INF) {
                maxdist[i]=max(maxdist[i],dist[i][j]);
                oldmax=max(oldmax,dist[i][j]);
            }
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if (dist[i][j]==INF) {
                double newmax=maxdist[i]+maxdist[j]+crs[i].dist_to(crs[j]);
                if (newmax>oldmax) ans=min(ans,newmax);
                else {
                    cout<<fixed<<setprecision(6)<<oldmax;
                    return 0;
                }
            }
        }
    cout<<fixed<<setprecision(6)<<ans;
}