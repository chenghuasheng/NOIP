//#1043. 「一本通 3.1 练习 1」新的开始
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin("newstart.in");
ofstream fout("newstart.out");
const int MAXN=300;
int v[MAXN+1];
int n;
long ans;
struct edge{
    int u,v,w;
    bool operator<(const edge other)const{
        return w<other.w;
    }
};
vector<edge> edges;

int sumw[MAXN+1],minv[MAXN+1];
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
    fin>>n;
    for(int i=1;i<=n;i++) fin>>v[i];
    
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            int p;
            fin>>p;
            if (i!=j){
                edges.push_back({i,j,p});
            }
        }
    for(int i=1;i<=n;i++){
        sumw[i]=0;
        minv[i]=v[i];
    }
    sort(edges.begin(),edges.begin()+edges.size());
    ufs.make_set();
    for(int i=0;i<edges.size();i++){
        int ru=ufs.find_set(edges[i].u);
        int rv=ufs.find_set(edges[i].v);
        if (ru!=rv){
            if (edges[i].w<minv[ru]||edges[i].w<minv[rv]){
                ufs.union_set(ru,rv);
                sumw[ru]+=edges[i].w;
                minv[ru]=min(minv[ru],minv[rv]);
                minv[rv]=0;
            }
        }
    }
    for(int i=1;i<=n;i++) ans+=sumw[i]+minv[i];
    fout<<ans;
}