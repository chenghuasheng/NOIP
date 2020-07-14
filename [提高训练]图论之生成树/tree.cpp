//#1046. 「一本通 3.1 练习 2」构造完全图
#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
ifstream fin("tree.in");
ofstream fout("tree.out");
const int MAXN=100000;
struct edge{
    int u,v,w;
    bool operator<(const edge other)const{
        return w<other.w;
    }
};
vector<edge> edges;
//并查集，由于需要枚举集合中的元素，故而要链式实现
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
int n;
int ans;
int main(){
    fin>>n;
    for(int i=1;i<n;i++){
        int s,t,d;
        fin>>s>>t>>d;
        edges.push_back({s,t,d});
    }
    sort(edges.begin(),edges.begin()+edges.size());
    ufs.make_set();
    for(int i=0;i<edges.size();i++){
        int ru=ufs.find_set(edges[i].u);
        int rv=ufs.find_set(edges[i].v);
        if (ru!=rv){
            ans+=edges[i].w;
            ans+=(ufs.ele[ru].length*ufs.ele[rv].length-1)*(edges[i].w+1);
            ufs.union_set(ru,rv);
        }
    }
    fout<<ans;
}