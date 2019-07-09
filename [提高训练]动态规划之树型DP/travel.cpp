#include <vector>
#include <cstring>
#include <iostream>
using namespace std;

FILE* fin;
FILE* fout;

const int MAXN=200000;
vector<int> graph[MAXN];
int dp_max1[MAXN];//dp_max1[i]表示以i为根的子树中，以i为末尾结点的最长路径
int dp_max2[MAXN];//dp_max2[i]表示以i为根的子树中的最长路径
int dp_next[MAXN];//似乎没用到了

bool on_max_path[MAXN];
int last_max_len;
int n;
int parent[MAXN];
void dp(int u){
    int count=graph[u].size();
    int s=0;
    int s2=0;
    int next=-1;
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (v!=parent[u]){
            parent[v]=u;
            dp(v);
            if (dp_max1[v]>s){
                s=dp_max1[v];
                next=v;
            }
            if (dp_max2[v]>s2) s2=dp_max2[v];
        }
    }
    dp_max1[u]=1+s;
    dp_max2[u]=s2;
    dp_next[u]=next;
    for(int k1=0;k1<count;k1++){
        int v1=graph[u][k1];
        if (parent[v1]!=u) continue;
        for(int k2=k1+1;k2<count;k2++){
            int v2=graph[u][k2];
            if (parent[v2]!=u) continue;
            int len=dp_max1[v1]+dp_max1[v2]+1;
            if (len>dp_max2[u]) dp_max2[u]=len;
        }
    }
    if (dp_max1[u]>dp_max2[u]) dp_max2[u]=dp_max1[u];
}
void dfs1(int u,int len){
    if (len<=0) return;
    if (dp_max1[u]==len){
        on_max_path[u]=true;
        int count=graph[u].size();
        for(int k=0;k<count;k++){
            int v=graph[u][k];
            if (parent[v]==u&&dp_max1[v]==len-1){
                dfs1(v,len-1);
            }
        }
    }
}
void dfs2(int u,int len){
    if (len<=0) return;
    if (dp_max1[u]==len) dfs1(u,len);
    int count=graph[u].size();
    for(int k=0;k<count;k++){
        int v=graph[u][k];
        if (parent[v]==u&&dp_max2[v]==len){
            dfs2(v,len);
        }
    }
    for(int k1=0;k1<count;k1++){
        int v1=graph[u][k1];
        if (parent[v1]!=u) continue;
        for(int k2=k1+1;k2<count;k2++){
            int v2=graph[u][k2];
            if (parent[v2]!=u) continue;
            if (len==dp_max1[v1]+dp_max1[v2]+1){
                on_max_path[u]=true;
                dfs1(v1,dp_max1[v1]);
                dfs1(v2,dp_max1[v2]);
            }
        }
    }
}
int main(){
    fin=fopen("travel.in","r");
    fout=fopen("travel.out","w");
    fscanf(fin,"%d",&n);
    for(int i=0;i<n-1;i++){
        int u,v;
        fscanf(fin,"%d %d",&u,&v);
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    memset(parent,-1,sizeof(parent));
    dp(0);
    last_max_len=dp_max2[0];
    //cout<<dp_max2[0]<<endl;
    //cout<<dp_max[0]<<endl;
    dfs2(0,last_max_len);
    
    for(int i=0;i<n;i++) 
        if (on_max_path[i]) fprintf(fout,"%d\n",i);//fout<<i<<endl;
}