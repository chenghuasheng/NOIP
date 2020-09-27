#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#define ll long long
using namespace std;
const int MAXN=100000;
const int MAXM=300000;
const ll MAXW=1000000000;
struct Edge{
    int  u,v;
    ll w;
    bool operator<(const Edge other)const{
        return w<other.w;
    }
};
Edge edges[MAXM+1];
int ecount;
bool in_tree[MAXM];
int tree_ecount;
vector<Edge> tree[MAXN+1];

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
int n,m;
ll kurskal(){
    ll ret=0;
    tree_ecount=0;
    ufs.make_set();
    for(int k=0;k<ecount;k++){
        int x=edges[k].u;
        int y=edges[k].v;
        int rx=ufs.find_set(x);
        int ry=ufs.find_set(y);
        if (rx!=ry){
            ufs.union_set(x,y);
            ret+=edges[k].w;
            tree[x].push_back({0,y,edges[k].w});
            tree[y].push_back({0,x,edges[k].w});
            in_tree[k]=true;
            tree_ecount++;
        }
        if (tree_ecount>=n-1) break;
    }
    return ret;
}
int deep[MAXN+1];
int f[MAXN+1][21];
ll maxw[MAXN+1][21];
ll secmaxw[MAXN+1][21];

void pre(int u,int fa,ll w){
    f[u][0]=fa;
    deep[u]=deep[fa]+1;
    maxw[u][0]=w;
    secmaxw[u][0]=-1;
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k].v;
        ll w=tree[u][k].w;
        if (v!=fa){
            pre(v,u,w);
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
ll find_maxw_less(int x,int y,ll w){
    int ca=lca(x,y);
    ll ret=-1;
    int node[2]={x,y};
    for(int i=0;i<2;i++){
        int p=node[i];
        for(int i=20;i>=0;i--){
            if (deep[f[p][i]]>=deep[ca]){
                if (maxw[p][i]<w) ret=max(ret,maxw[p][i]);
                else ret=max(ret,secmaxw[p][i]);
                p=f[p][i];
            }
        }
    }
    return ret;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=0;i<m;i++){
        int x,y;
        ll z;
        scanf("%d %d %lld",&x,&y,&z);
        if (x==y) continue;
        edges[ecount]={x,y,z};
        ecount++;
    }
    
    sort(edges,edges+ecount);
    ll min_tree=kurskal();
    pre(1,0,0);
    for(int i=1;i<=20;i++)
        for(int x=1;x<=n;x++){
            f[x][i]=f[f[x][i-1]][i-1];
            maxw[x][i]=max(maxw[x][i-1],maxw[f[x][i-1]][i-1]);
            secmaxw[x][i]=min(maxw[x][i-1],maxw[f[x][i-1]][i-1]);
            if ((secmaxw[x][i]==maxw[x][i])||(secmaxw[x][i]<max(secmaxw[x][i-1],secmaxw[f[x][i-1]][i-1])))
            secmaxw[x][i]=max(secmaxw[x][i-1],secmaxw[f[x][i-1]][i-1]);
        }
    ll second_min_tree=MAXW*MAXN;
    for(int k=0;k<ecount;k++){
        if (!in_tree[k]){
            int x=edges[k].u;
            int y=edges[k].v;
            ll w=edges[k].w;
            ll maxw=find_maxw_less(x,y,w);
            if (maxw>=0){
                second_min_tree=min(second_min_tree,min_tree+w-maxw);
            }
        }
    }
    printf("%lld",second_min_tree);
}