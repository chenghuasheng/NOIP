#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;
const int MAXN=1000;
const int MAXM=1000;
bool connected[MAXN+1][MAXN+1];
struct Edge{
    int u,v;
    double w;
    bool operator <(const Edge other)const{
        return w<other.w;
    }
};
struct Coor{
    double x,y;
    double dist_to(const Coor other){
        return sqrt((x-other.x)*(x-other.x)+(y-other.y)*(y-other.y));
    }
};
Edge edges[MAXN*MAXN/2+1];
int ecount;
int n,m;
Coor coors[MAXN+1];

struct node{
    int head,next,last,length;
};
struct union_find_set{
    node ele[MAXN+1];
    void make_set(){
        for(int i=1;i<=MAXN;i++) ele[i]={i,0,i,1};
    }
    void union_set(int x,int y){
        int hx=find_set(x);
        int hy=find_set(y);
        if (hx!=hy){
            if (ele[hx].length<ele[hy].length) add_to(hx,hy);
            else add_to(hy,hx);
        }
    }
    int find_set(int x){
        return ele[x].head;
    }
    void add_to(int head_from,int head_to){
        ele[ele[head_to].last].next=head_from;
        ele[head_to].last=ele[head_from].last;
        ele[head_to].length+=ele[head_from].length;
        int cur=head_from;
        while(cur!=0){
            ele[cur].head=head_to;
            cur=ele[cur].next;
        }
    }
};
union_find_set ufs;
double ans;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        int x,y;
        cin>>x>>y;
        coors[i]={x,y};
    }
    ufs.make_set();
    for(int i=1;i<=m;i++){
        int u,v;
        cin>>u>>v;
        connected[u][v]=true;
        connected[v][u]=true;
        ufs.union_set(u,v);
    }
    for(int u=1;u<=n;u++)
        for(int v=u+1;v<=n;v++){
            if (!connected[u][v]){
                edges[ecount]={u,v,coors[u].dist_to(coors[v])};
                ecount++;
            }
        }
    sort(edges,edges+ecount);
    
    for(int i=0;i<ecount;i++){
        int x=edges[i].u;
        int y=edges[i].v;
        int rx=ufs.find_set(x);
        int ry=ufs.find_set(y);
        if (rx!=ry){
            ufs.union_set(x,y);
            ans+=edges[i].w;
        }
    }
    cout<<fixed<<setprecision(2)<<ans;
}

