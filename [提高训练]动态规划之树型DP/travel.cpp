#include <fstream>
#include <vector>
#include <cstring>

using namespace std;
ifstream fin("travel.in");
ofstream fout("travel.out");

const int MAXN=200000;
vector<int> graph[MAXN];
int dp_max1[MAXN];//dp_max1[i]表示以i为根的子树中，根i到叶子结点的最长路径长度
int dp_max2[MAXN];//dp_max2[i]表示以i为根的子树中，根i到叶子结点的次长路径长度
int dp_max3[MAXN];//dp_max2[i]表示以i为根的子树的直径


bool on_max_path[MAXN];
int last_max_len;
int n;
int parent[MAXN];
void dp(int u){
    int count=graph[u].size();
    int s1=0;
    int s2=0;
    int s3=0;
    int next=-1;
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (v!=parent[u]){
            parent[v]=u;
            dp(v);
            if (dp_max1[v]+1>s1) {
                s2=s1;
                s1=dp_max1[v]+1;
            }else if (dp_max1[v]+1>s2) 
                s2=dp_max1[v]+1;
            if (dp_max3[v]>s3) s3=dp_max3[v];
        }
    }
    dp_max1[u]=s1;
    dp_max2[u]=s2;
    dp_max3[u]=max(dp_max1[u]+dp_max2[u],s3);
}
//在以u为根的子树下，搜根u到叶子结点长度为len的路径
void dfs1(int u,int len){
    if (len<0) return;//只有一个节点的时候，它的长度为0，也要搜索
    on_max_path[u]=true;
    int count=graph[u].size();
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (parent[v]==u&&dp_max1[v]==len-1){
            dfs1(v,len-1);
        }
    }
}
//在以u为根的子树下，搜索长度为len的直径
void dfs2(int u,int len){
    if (len<0) return;
    if (dp_max1[u]+dp_max2[u]==len){
        dfs1(u,dp_max1[u]);
        dfs1(u,dp_max2[u]);
    }
    int count=graph[u].size();
    
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (parent[v]!=u) continue;
        if (dp_max3[v]==len) dfs2(v,len);
    }
}
int main(){
    fin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;
        fin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    memset(parent,-1,sizeof(parent));
    dp(0);
    last_max_len=dp_max3[0];
    dfs2(0,last_max_len);
    for(int i=0;i<n;i++) 
        if (on_max_path[i]) fout<<i<<endl;
}