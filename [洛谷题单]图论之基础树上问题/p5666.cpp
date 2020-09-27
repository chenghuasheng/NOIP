#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>

using namespace std;
const int MAXN=299995;
struct Edge{
    int u,v;
};
Edge edges[MAXN+1];
int ecount=0;
int n,t;
vector<int> tree[MAXN+1];
int size[MAXN+1];
int parent[MAXN+1];
int root;
long long ans;
int read(){
    int ret=0;
    char c=getchar();
    while(c>='0'&&c<='9'){
        ret=ret*10+c-'0';
        c=getchar();
    }
    return ret;
}
void dfs1(int u){
    size[u]=1;
    bool iszx=true;
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k];
        if (v!=parent[u]){
            parent[v]=u;
            dfs1(v);
            size[u]+=size[v];
        }
        if (size[v]>n/2) iszx=false;
    }
    if (n-size[u]>n/2) iszx=false;
    if (iszx) root=u;
}

int max_sub_size[MAXN+1];
int max_sub_tree[MAXN+1];
int second_max_sub_tree[MAXN+1];
int second_max_sub_size[MAXN+1];
int in_sub_tree[MAXN+1];
int f[MAXN+1][21];
void dfs2(int u){
    size[u]=1;
    if (u==root||parent[u]==root) in_sub_tree[u]=u;
    else in_sub_tree[u]=in_sub_tree[parent[u]];
    for(int k=0;k<tree[u].size();k++){
        int v=tree[u][k];
        if (v!=parent[u]){
            parent[v]=u;
            dfs2(v);
            size[u]+=size[v];
            if (size[v]>max_sub_size[u]){
                second_max_sub_size[u]=max_sub_size[u];
                second_max_sub_tree[u]=max_sub_tree[u];
                max_sub_size[u]=size[v];
                max_sub_tree[u]=v;
            }else if (size[v]>second_max_sub_size[u]){
                second_max_sub_size[u]=size[v];
                second_max_sub_tree[u]=v;
            }
        }
    }
    f[u][0]=max_sub_tree[u];
}
void find(int u,int total){
    // bool iszx=true;
    // if (total-size[u]>total/2) iszx=false;
    // if (max_sub_size[u]>0){
    //     if (max_sub_size[u]>total/2) iszx=false;
    //     if (max_sub_size[u]>=total/2) find(max_sub_tree[u],total);
    // }
    // if (iszx) ans+=u;
    for(int i=20;i>=0;i--){
        int t=f[u][i];
        if (t>0&&max_sub_size[t]>total/2) u=t;
    }
    if (f[u][0]==0) ans+=u;
    else {
        if (max_sub_size[u]>total/2) u=f[u][0];
        if (total-size[u]<=total/2) ans+=u;
        u=f[u][0];
        if (total-size[u]<=total/2) ans+=u;
    }
}
int main(){
    t=read();
    for(int k=0;k<t;k++){
        n=read();
        for(int i=1;i<=n;i++) tree[i].clear();
        memset(size,0,sizeof(size));
        memset(parent,0,sizeof(parent));
        memset(max_sub_size,0,sizeof(max_sub_size));
        memset(max_sub_tree,0,sizeof(max_sub_tree));
        memset(second_max_sub_size,0,sizeof(second_max_sub_size));
        memset(second_max_sub_tree,0,sizeof(second_max_sub_tree));
        ecount=0;
        ans=0;
        for(int i=1;i<n;i++){
            int a,b;
            a=read();b=read();
            tree[a].push_back(b);
            tree[b].push_back(a);
            edges[ecount]={a,b};
            ecount++;
        }
        dfs1(1);
        memset(size,0,sizeof(size));
        memset(parent,0,sizeof(parent));
        dfs2(root);
        for(int i=1;i<=20;i++)
            for(int u=1;u<=n;u++) 
                f[u][i]=f[f[u][i-1]][i-1];
        
        for(int i=0;i<ecount;i++){
            int u=edges[i].u;
            int v=edges[i].v;
            if (v==parent[u]) swap(u,v);
            find(v,size[v]);
            if (in_sub_tree[v]!=max_sub_tree[root]){
                find(root,n-size[v]);
            }else {
                int max_size=max_sub_size[root]-size[v];
                int max_tree=max_sub_tree[root];
                if (max_size>=second_max_sub_size[root]){
                    ans+=root;
                    if (max_tree!=v&&(n-size[v]-max_size<=(n-size[v])/2)) ans+=max_tree;
                }else{
                    max_size=second_max_sub_size[root];
                    max_tree=second_max_sub_tree[root];
                    if (max_size<=(n-size[v])/2) {
                        ans+=root;
                        if (n-size[v]-max_size<=(n-size[v])/2) ans+=max_tree;
                    }else find(max_tree,n-size[v]);
                }
            }
        }
        cout<<ans<<endl;
    }
}