#include <iostream>
#include <vector>
using namespace std;
const int MAXN=1000000;
struct Edge{
    int u,v,w;
};
Edge edges[MAXN];
vector<int> G[MAXN+1];
int parent[MAXN+1];
int size[MAXN+1];
int n;
long long sum;

void dfs(int u,int fa){
    size[u]=1;
    parent[u]=fa;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
           dfs(v,u);
           size[u]+=size[v];     
        }
    }
}
int main(){
    cin>>n;
    for(int i=0;i<n-1;i++){
        int a,b,c;
        cin>>a>>b>>c;
        edges[i]={a,b,c};
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1,0);
    for(int i=0;i<n-1;i++){
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;
        if (parent[u]==v) swap(u,v);
        long long t=n-2*size[v];
        sum+=t*w;
    }
    cout<<sum;
}