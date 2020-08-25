//P5836 [USACO19DEC]Milk Visits S
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>;

using namespace std;
const int MAXN=100000;
const int MAXJ=20;
int n,m;
char cow[MAXN+1];
vector<int> G[MAXN+1];
int parent[MAXN+1];
int f[MAXN+1][MAXJ+1];
int d[MAXN+1];
int sum_hcow[MAXN+1];//从根到此节点H的累计数
int sum_gcow[MAXN+1];//从根到此节点G的累计数
//深搜预处理每个节点的深度和他的父节点（即f[x][0])
void pre(int x,int fa){
    if (cow[x]=='H') {
        sum_hcow[x]=sum_hcow[fa]+1;
        sum_gcow[x]=sum_gcow[fa];
    }else {
        sum_hcow[x]=sum_hcow[fa];
        sum_gcow[x]=sum_gcow[fa]+1;
    }
    f[x][0]=fa;
    d[x]=d[fa]+1;
    for(int k=0;k<G[x].size();k++){
        int y=G[x][k];
        if (y!=fa){
            pre(y,x);
        }
    }
}
//求两个节点的公共祖先
int lca(int x,int y){
    if (d[x]<d[y]) swap(x,y);
    for(int j=MAXJ;j>=0;j--) if (d[f[x][j]]>=d[y]) x=f[x][j];//先通过跳让两个节点的深度一致
    if (x==y) return y;
    for(int j=MAXJ;j>=0;j--) //如果不同继续跳
        if (f[x][j]!=f[y][j]) { 
            x=f[x][j];
            y=f[y][j];
        }
    return f[x][0];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>cow[i];
    for(int k=1;k<n;k++){
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    pre(1,0);//预处理计算出每个节点跳2^0次到达的节点
    //倍增计算出每个节点跳2^j次到达的节点(1<=j<=20)
    for(int j=1;j<=MAXJ;j++)
        for(int i=1;i<=n;i++){
            f[i][j]=f[f[i][j-1]][j-1];
        }
    
    for(int i=1;i<=m;i++){
        int a,b;
        char c;
        cin>>a>>b>>c;
        if (cow[a]==c||cow[b]==c) cout<<1;
        else {
            int gf=lca(a,b);
            if (cow[gf]==c) cout<<1;
            else {
                if (c=='H') {
                    if (sum_hcow[a]-sum_hcow[gf]>0||sum_hcow[b]-sum_hcow[gf]>0) cout<<1;
                    else cout<<0;
                }else {
                    if (sum_gcow[a]-sum_gcow[gf]>0||sum_gcow[b]-sum_gcow[gf]>0) cout<<1;
                    else cout<<0;
                }
            }
        }
    }
    //system("pause");
}