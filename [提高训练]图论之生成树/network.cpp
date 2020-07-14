//#1042. 「一本通 3.1 例 2」北极通讯网络
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
const int MAXN=500;

ifstream fin("network.in");
ofstream fout("network.out");

struct position{
    int x,y;
    double disto(const position other){
        double xdeta=x-other.x;
        double ydeta=y-other.y;
        return sqrt(xdeta*xdeta+ydeta*ydeta);
    }
};
struct edge{
    int u,v;
    double w;
    bool operator<(const edge other)const{
        return w<other.w;
    }
};
int n,k;
vector<edge> edges;
position positions[MAXN+1];

struct union_find_set{
    int father[MAXN+1];
    void make_set(){
        for(int i=1;i<=MAXN;i++) father[i]=i;
    }
    int find_set(int x){
        while(father[x]!=x) x=father[x];
        return x;
    }
    void union_set(int x,int y){
        int hx=find_set(x);
        int hy=find_set(y);
        while(father[y]!=y){
            int p=father[y];
            father[y]=hx;
            y=p;
        }
        father[hy]=hx;
    }
};
union_find_set ufs;

int main(){
    fin>>n>>k;
    for(int i=1;i<=n;i++){
        int x,y;
        fin>>x>>y;
        positions[i]={x,y};
    }
    for(int u=1;u<=n;u++)
        for(int v=1;v<=n;v++){
            if (u!=v) {
                double w=positions[u].disto(positions[v]);
                edges.push_back({u,v,w});
            }
        }
    sort(edges.begin(),edges.begin()+edges.size());
    int m=n-k;
    ufs.make_set();
    int c=0;
    for(int i=0;i<edges.size();i++){
        if (ufs.find_set(edges[i].u)!=
        ufs.find_set(edges[i].v)){
            c++;
            ufs.union_set(edges[i].u,edges[i].v);
            if (c==m){
                fout.setf(ios::fixed,ios::floatfield);
                fout.precision(2);
                fout<<edges[i].w;
                break;
            }
        }
    }
}   

