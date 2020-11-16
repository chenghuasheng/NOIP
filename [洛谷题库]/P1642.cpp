#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
const int MAXN=100;
const double INF=100000000;
const double e=0.0000001;
int n,m;
int v[MAXN+1],w[MAXN+1];
vector<int> G[MAXN+1];
double ans;
double dp_f[MAXN+1][MAXN+1];
int sz[MAXN+1];


void tree_dp(int u,int fa){
   sz[u]=1;
   dp_f[u][0]=0;
   for(int k=0;k<G[u].size();k++){
        int v=G[u][k];
        if (v!=fa){
            tree_dp(v,u);
            sz[u]+=sz[v];
            for(int i=sz[u]-1;i>0;i--)
                    for(int j=0;j<=min(i,sz[v]);j++) dp_f[u][i]=max(dp_f[u][i],dp_f[u][i-j]+dp_f[v][j]);
        }
   }
   for(int i=sz[u];i>=1;i--) dp_f[u][i]=dp_f[u][i-1]+(double)v[u]-ans*(double)w[u]; 
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>v[i];
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int i=1;i<n;i++){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    double left=0.0;
    double right=10000;
    
    while(right-left>e){
        ans=(left+right)/2.0;
        for(int i=1;i<=n;i++) 
            for(int j=0;j<=n;j++) {
                dp_f[i][j]=-1*INF;
                sz[i]=0;
            }
        tree_dp(1,0);
        double f=-1*INF;
        for(int i=1;i<=n;i++) 
            f=max(f,dp_f[i][n-m]);
        if (f>e) left=ans;
        else right=ans;
    }
    cout<<fixed<<setprecision(1)<<left;
}