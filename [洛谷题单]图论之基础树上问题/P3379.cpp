#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;
const int MAXN=500000;
int n,m,r;
vector<int> tree[MAXN+1];
int f[MAXN+1][21];
int deep[MAXN+1];

void pre(int u,int fa){
    deep[u]=deep[fa]+1;
    f[u][0]=fa;
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k];
        if (v!=fa){
            pre(v,u);
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
int main(){
    scanf("%d %d %d",&n,&m,&r);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        tree[x].push_back(y);
        tree[y].push_back(x);
    }
    pre(r,0);
    for(int i=1;i<=20;i++)
        for(int x=1;x<=n;x++)
            f[x][i]=f[f[x][i-1]][i-1];
    for(int i=1;i<=m;i++){
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",lca(a,b));
    }
}