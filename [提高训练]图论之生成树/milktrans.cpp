//#1047. 「一本通 3.1 练习 3」秘密的牛奶运输
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
ifstream fin("milktrans.in");
ofstream fout("milktrans.out");
const int MAXN=500;
const int MAXM=10000;
int w[MAXN+1][MAXN+1];
struct edge{
    int u,v,w;
    bool operator<(const edge other)const{
        return w<other.w;
    }
};
vector<edge> edges;
vector<int> min_tree;
bool erased[MAXM];

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
int n,m;

int main(){
    fin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,z;
        fin>>x>>y>>z;
        if (z!=w[x][y]) {
            edges.push_back({x,y,z});
            w[x][y]=z;
        }
    }
    sort(edges.begin(),edges.begin()+edges.size());
    //for(int i=0;i<edges.size();i++) 
    //    cout<<edges[i].u<<' '<<edges[i].v<<' '<<edges[i].w<<endl;
    cout<<edges.size()<<endl;
    //找出最小生成树
    ufs.make_set();
    long long min_sum=0;
    for(int i=0;i<edges.size();i++){
        int ru=ufs.find_set(edges[i].u);
        int rv=ufs.find_set(edges[i].v);
        if (ru!=rv){
            min_tree.push_back(i);//最小生成树中边的编号
            min_sum+=edges[i].w;
            ufs.union_set(ru,rv);
        }
    }
    cout<<min_sum<<endl;
    //枚举去掉最小生成树的一条边后，再生成的最小生成树
    //找出最小的权值
    long long ans=0x7fffffffffffffff;
    for(int k=0;k<min_tree.size();k++){
        int j=min_tree[k];
        erased[j]=true;
        ufs.make_set();
        long long sum=0;
        for(int i=0;i<edges.size();i++){
            if (erased[i]) continue;
            int ru=ufs.find_set(edges[i].u);
            int rv=ufs.find_set(edges[i].v);
            if (ru!=rv){
                sum+=edges[i].w;
                ufs.union_set(ru,rv);
            }
        }
        //cout<<sum<<endl;
        if (sum>min_sum) ans=min(ans,sum);
        erased[j]=false;
    }
    fout<<ans;
}