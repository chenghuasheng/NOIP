//#1015. 「一本通 5.2 练习 4」叶子的染色 
#include <fstream>
#include <vector>
#include <cstring>
#include <iostream>

using namespace std;
ifstream fin("leaf.in");
ofstream fout("leaf.out");

const int MAXM=10000;
const int INF=0x7fffffff;
int m,n;
int color[MAXM+1];
vector<int> tree[MAXM+1];
int dp_min[MAXM+1][2];//dp_min[i][j]表示以i为根的子树中，根结点i着色j时最少的着色点数
bool visited[MAXM+1];

void dp(int i){
    visited[i]=true;
    if (color[i]>-1) return;
    int s=tree[i].size();
    int s0=0,s1=0;
    for(int k=0;k<s;k++){
        int j=tree[i][k];
        if (!visited[j]) {
            dp(j);
            s0+=min(dp_min[j][0]-1,dp_min[j][1]);
            s1+=min(dp_min[j][0],dp_min[j][1]-1);
        }
    }
    dp_min[i][0]=s0+1;
    dp_min[i][1]=s1+1;
}

int main(){
    fin>>m>>n;
    memset(color,-1,sizeof(color));
    for(int i=1;i<=n;i++) {
        fin>>color[i];
        dp_min[i][color[i]]=1;
        dp_min[i][1-color[i]]=INF;
    }
    for(int i=0;i<m;i++){
        int a,b;
        fin>>a>>b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    memset(visited,false,sizeof(visited));
    dp(n+1);
    int ans=min(dp_min[n+1][0],dp_min[n+1][1]);
    fout<<ans;
}