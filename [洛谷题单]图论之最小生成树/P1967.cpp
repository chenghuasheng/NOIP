#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;
const int MAXN=10000;
const int MAXM=50000;
const int INF=0x3fffffff;
struct Edge{
    int u,v,w;
    bool operator<(const Edge other)const{
        return w>other.w;
    }
};
vector<Edge> tree[MAXN+1];
Edge edges[MAXM];
int n,m,q;
int ecount;

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
int deep[MAXN+1];
int root[MAXN+1];
int weight_to_parent[MAXN+1];
int f[MAXN+1][21];

void pre(int u,int fa,int w,int r){
    f[u][0]=fa;
    deep[u]=deep[fa]+1;
    weight_to_parent[u]=w;
    root[u]=r;
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k].v;
        int w=tree[u][k].w;
        if (v!=fa){
            pre(v,u,w,r);
        }
    }
}
int lca(int x,int y){
    if (deep[x]<deep[y]) swap(x,y);
    for(int i=20;i>=0;i--) 
        if (deep[f[x][i]]>=deep[y]) x=f[x][i];
    if (x==y) return x;
    for(int i=20;i>=0;i--){
        if (f[x][i]!=f[y][i]){
            x=f[x][i];
            y=f[y][i];
        }
    }
    return f[x][0];
}
//下面这个查找最小边其实可以用倍增来维护，只不过此题的数据没有那么大
int search(int x,int y){
    if (root[x]!=root[y]) return -1;
    int ca=lca(x,y);
    int ret=INF;
    while(x!=ca){
        ret=min(ret,weight_to_parent[x]);
        x=f[x][0];
    }
    while(y!=ca){
        ret=min(ret,weight_to_parent[y]);
        y=f[y][0];
    }
    return ret;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int x,y,z;
        scanf("%d %d %d",&x,&y,&z);
        edges[ecount]={x,y,z};
        ecount++;
    }
    sort(edges,edges+ecount);
    ufs.make_set();
    for(int i=0;i<ecount;i++){
        int x=edges[i].u;
        int y=edges[i].v;
        int rx=ufs.find_set(x);
        int ry=ufs.find_set(y);
        if (rx!=ry){
            ufs.union_set(x,y);
            tree[x].push_back({0,y,edges[i].w});
            tree[y].push_back({0,x,edges[i].w});
        }
    }
    for(int i=1;i<=n;i++) 
        if (root[i]==0) pre(i,0,0,i);
    for(int i=1;i<=20;i++)
        for(int x=1;x<=n;x++)
            f[x][i]=f[f[x][i-1]][i-1];
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        int t=search(x,y);
        printf("%d\n",t);
    }
}