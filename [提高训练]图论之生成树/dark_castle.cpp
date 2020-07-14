//#1041. 「一本通 3.1 例 1」黑暗城堡
#include <fstream>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
ifstream fin("dark_castle.in");
ofstream fout("dark_castle.out");

const int MAXN=1000;
const int INF=0x7fffffff;
struct edge{
    int v;
    int w;
};
vector<edge> graph[MAXN+1];
int d[MAXN+1];
struct node {
    int v;
    bool operator<(const node other) const
    {
        return d[v] > d[other.v]; //小顶堆
    }
};
priority_queue<node> minheap;
int n,m;
long long ans;
void dijikstra(){
    d[1]=0;
    minheap.push({1});
    while(!minheap.empty()){
        node cur=minheap.top();
        minheap.pop();
        int u=cur.v;
        int s=graph[u].size();
        for(int k=0;k<s;k++){
            int v=graph[u][k].v;
            int w=graph[u][k].w;
            if (d[u]+w<d[v]){
                d[v]=d[u]+w;
                minheap.push({v});
            }
        }
    }
}
void solve(){
    for(int i=2;i<=n;i++) minheap.push({i});
    ans=1;
    while(!minheap.empty()){
        node cur=minheap.top();
        minheap.pop();
        int u=cur.v;
        int s=graph[u].size();
        int p=0;
        
        for(int k=0;k<s;k++){
            int v=graph[u][k].v;
            int w=graph[u][k].w;
            if (d[u]==d[v]+w) p++;
        }
        //cout<<p<<endl;
        ans=ans*p;
    }
}
int main(){
    fin>>n>>m;
    for(int i=0;i<m;i++){
        int x,y,l;
        fin>>x>>y>>l;
        graph[x].push_back({y,l});
        graph[y].push_back({x,l});
    }
    for(int i=1;i<=n;i++) d[i]=INF;
    dijikstra();
    solve();
    fout<<ans;
}