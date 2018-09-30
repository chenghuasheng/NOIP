//¶àÖØ±³°ü£ºhttp://www.joyoi.cn/problem/codevs-5429
#include<iostream>
using namespace std;
int n,m;
int w[7001],v[7001],c[7001];
int  dp[7001][7001];

int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>v[i]>>w[i]>>c[i];
	}
		
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			dp[i][j]=dp[i][j-1];
			t=min(i/v[j],c[j]);
			for(int k=1;k<=t;k++) {
				dp[i][j]=max(dp[i-k*v[j]][j-1]+k*w[j],dp[i][j]);
			}		
		} 
	
	cout<<dp[m][n];		
}
