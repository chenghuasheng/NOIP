//P4281 [AHOI2008]紧急集合 / 聚会
//此题有两组很卡时间，用快读的效果和scanf差不多，有时能过有时不能过
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;
const int MAXN=500000;
const int MAXJ=20;
int n,m;
vector<int> G[MAXN+1];
int d[MAXN+1];
int f[MAXN+1][MAXJ+1];
void pre(int u,int fa){
    d[u]=d[fa]+1;
    f[u][0]=fa;
    for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
            pre(v,u);
        }
    }
}
int lca(int x,int y){
    if (d[x]<d[y]) swap(x,y);
    for(int j=MAXJ;j>=0;j--) if (d[f[x][j]]>=d[y]) x=f[x][j];
    if (x==y) return x;
    for(int j=MAXJ;j>=0;j--) 
        if (f[x][j]!=f[y][j]){
            x=f[x][j];
            y=f[y][j];
        }
    return f[x][0];
}
int main(){
    //cin>>n>>m;
    scanf("%d %d",&n,&m);
    for(int i=1;i<n;i++){
        int a,b;
        //cin>>a>>b;
        scanf("%d %d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
    }

    pre(1,0);
    for(int j=1;j<=MAXJ;j++)
        for(int u=1;u<=n;u++)
            f[u][j]=f[f[u][j-1]][j-1];
    for(int i=0;i<m;i++){
        int x,y,z;
        //cin>>x>>y>>z;
        scanf("%d %d %d",&x,&y,&z);
        int w=lca(x,y);
        int w1=lca(y,z);
        int w2=lca(z,x);
        int choose;
        int ans=0;
        if (d[w]>=d[w1]&&d[w]>=d[w2]) {
            choose=w;
            ans=d[x]-d[w]+d[y]-d[w]+d[w]-d[w1]+d[z]-d[w1];
        }
        else if (d[w1]>=d[w]&&d[w1]>=d[w2]) {
            choose=w1;
            ans=d[z]-d[w1]+d[y]-d[w1]+d[w1]-d[w]+d[x]-d[w];
        }else {
            choose=w2;
            ans=d[z]-d[w2]+d[x]-d[w2]+d[w2]-d[w1]+d[y]-d[w1];
        }
        //cout<<choose<<' '<<ans<<endl;
        printf("%d %d\n",choose,ans);
    }
    system("pause");
}
