#include <iostream>
using namespace std;
const int MAXN=500;
int n;
int c[MAXN+1];
int dp[MAXN+1][MAXN+1];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i];
    for(int i=1;i<=n;i++) dp[i][i]=1;
    for(int i=1;i<=n-1;i++) 
        if (c[i]==c[i+1]) dp[i][i+1]=1;
        else dp[i][i+1]=2;
    for(int len=3;len<=n;len++)
        for(int i=1;i<=n-len+1;i++){
            int j=i+len-1;
            dp[i][j]=dp[i][i]+dp[i+1][j];
            for(int k=i+1;k<j;k++) dp[i][j]=min(dp[i][j],dp[i][k]+dp[k+1][j]);
            if (c[i]==c[j]) dp[i][j]=min(dp[i][j],dp[i+1][j-1]);
        }
    cout<<dp[1][n];
}