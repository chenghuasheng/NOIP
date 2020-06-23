#include <iostream>
using namespace std;
const int MAXN=10000;
int n;
int a[MAXN+1],b[MAXN+1];
int dp[MAXN+1][MAXN+1];

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            if (a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
            else {
                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            }
        }
    cout<<dp[n][n];
}