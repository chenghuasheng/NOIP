#include<fstream>
#include<cmath>
using namespace std;
ifstream fin("marathon.in");
ofstream fout("marathon.out");
struct CITY{
    int x=0;
    int y=0;
    int distance_to(CITY other){
        return abs(x-other.x)+abs(y-other.y);
    }
};
const int MAXN=100001;
CITY cities[MAXN];
int total_dis[MAXN];
int min_dis[MAXN];

int n;
int main(){
    fin>>n;
    for(int i=1;i<=n;i++){
        fin>>cities[i].x>>cities[i].y;
    }
    total_dis[1]=0;
    for(int i=2;i<=n;i++) total_dis[i]=total_dis[i-1]+cities[i-1].distance_to(cities[i]);
    min_dis[1]=0;
    min_dis[2]=total_dis[2];
    for(int i=3;i<=n;i++){
        int d1=total_dis[i-2]+cities[i-2].distance_to(cities[i]);
        int d2=min_dis[i-1]+cities[i-1].distance_to(cities[i]);
        min_dis[i]=min(d1,d2);
    }
    fout<<min_dis[n];
}