#include <iostream>
using namespace std;
const int MAXN=100;
int r,c;
int high[MAXN][MAXN];
int dp[MAXN][MAXN];
int direct_offset[4][2]={{0,1},{0,-1},{-1,0},{1,0}};
void tree_dp(int i,int j){
    int maxsublength=0;
    for(int k=0;k<4;k++){
        int newi=i+direct_offset[k][0];
        int newj=j+direct_offset[k][1];
        if (newi<0||newi>=r||newj<0||newj>=c) continue;
        if (high[i][j]<=high[newi][newj]) continue;
        if (dp[newi][newj]==0) tree_dp(newi,newj);
        maxsublength=max(maxsublength,dp[newi][newj]);
    }
    dp[i][j]=maxsublength+1;
}
int ans;
int main(){
    cin>>r>>c;
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) cin>>high[i][j];
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++) {
            if (dp[i][j]==0) tree_dp(i,j);
            ans=max(ans,dp[i][j]);
        }
    cout<<ans;
}
