//P3398 仓鼠找sugar
#include <iostream>
#include <vector>
using namespace std;
const int MAXN=100000;
const int MAXJ=20;
int n,q;
vector<int> G[MAXN+1];
int deep[MAXN+1];
int f[MAXN+1][MAXJ+1];

void pre(int u,int fa){
    deep[u]=deep[fa]+1;
    f[u][0]=fa;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
            pre(v,u);
        }
    }
}
int lca(int x,int y){
    if (deep[x]<deep[y]) swap(x,y);
    for(int j=MAXJ;j>=0;j--)  if (deep[f[x][j]]>=deep[y]) x=f[x][j];
    if (x==y) return x;
    for(int j=MAXJ;j>=0;j--) 
        if (f[x][j]!=f[y][j]){
            x=f[x][j];
            y=f[y][j];
        }
    return f[x][0];
}
int main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    pre(1,0);
    
    for(int j=1;j<=MAXJ;j++)
        for(int u=1;u<=n;u++)
            f[u][j]=f[f[u][j-1]][j-1];
    
    for(int i=0;i<q;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        int ab=lca(a,b);
        int cd=lca(c,d);

        int ac=lca(a,c);
        int ad=lca(a,d);
        int bc=lca(b,c);
        int bd=lca(b,d);
        //用ab的两个点分别与cd的两个点交叉组合（ac,ac,bc,bd），只要存在一对点的lca均大于或等于ab和cd的lca，则说明两条路径有交点
        if((deep[ac]>=deep[ab]&&deep[ac]>=deep[cd])
            ||(deep[ad]>=deep[ab]&&deep[ad]>=deep[cd])
            ||(deep[bc]>=deep[ab]&&deep[bc]>=deep[cd])
            ||(deep[bd]>=deep[ab]&&deep[bd]>=deep[cd]))
            cout<<'Y'<<endl;
        else cout<<'N'<<endl;
    }
    //system("pause");
}