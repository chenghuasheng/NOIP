#include <iostream>
#include <cstring>

using namespace std;
const int MAXN=100;
const int MAXM=2000;
const int MOD=998244353;
int n,m;
int a[MAXN+1][MAXM+1];
long long sum[MAXN];//

long long all[MAXN+1];//all[i]表示前i种烹饪方法中符合1、2条件的所有方案数
long long dp[MAXN+1][MAXN+1][MAXN+1];

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            cin>>a[i][j];
            sum[i]=(sum[i]+a[i][j]) % MOD;
        }
    all[1]=sum[1];
    for(int i=2;i<=n;i++){
        all[i]=(all[i-1]+(all[i-1]*sum[i])% MOD+sum[i]) % MOD;
    }
    int t=0;
    for(int j=1;j<=m;j++){
        memset(dp,0,sizeof(dp));
        dp[1][1][0]=(sum[1]-a[1][j]+MOD) % MOD;
        dp[1][1][1]=a[1][j];
        for(int i=2;i<=n;i++){
            for(int k=1;k<=i;k++){
               for(int p=0;p<=k;p++){
                    dp[i][k][p]=dp[i-1][k][p] % MOD;
                    if (k>1) {
                        if (p<k) dp[i][k][p]=(dp[i][k][p]+(dp[i-1][k-1][p]*(sum[i]-a[i][j])) % MOD)% MOD;
                        if (p>0) dp[i][k][p]=(dp[i][k][p]+(dp[i-1][k-1][p-1]*a[i][j])% MOD)% MOD;
                    }
                    if (k==1){
                        if (p<k) dp[i][k][p]=(dp[i][k][p]+sum[i]-a[i][j]+MOD) % MOD;
                        if (p>0) dp[i][k][p]=(dp[i][k][p]+a[i][j])% MOD;
                    }
               } 
            }
        }
        for(int k=1;k<=n;k++)
            for(int p=k;p>k/2;p--){
                t=(t+dp[n][k][p]) % MOD;
            }
    }
    int ans=(all[n]-t+MOD) % MOD;
    cout<<ans;
}