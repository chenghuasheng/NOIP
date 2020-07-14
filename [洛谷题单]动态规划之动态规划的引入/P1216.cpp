#include <iostream>
using namespace std;
const int MAXR=1000;
int r;
int a[MAXR+1][MAXR+1];
int dp[MAXR+1][MAXR+1];
int ans;
int main(){
    cin>>r;
    for(int i=1;i<=r;i++)
        for(int j=1;j<=i;j++){
            cin>>a[i][j];
        }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=i;j++){
            dp[i][j]=max(dp[i-1][j-1],dp[i-1][j])+a[i][j];
        }
    }
    for(int j=1;j<=r;j++) ans=max(ans,dp[r][j]);
    cout<<ans;
}