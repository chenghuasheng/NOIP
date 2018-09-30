//01±³°ü£ºhttp://www.joyoi.cn/problem/codevs-5709 
#include<iostream>
using namespace std; 
long s;
int n;
long w[1001],k[1001];
long dp[5001][1001];
int main(){
	cin>>s;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>w[i]>>k[i];
	for(int i=1;i<=s;i++)
		for(int j=1;j<=n;j++){
			dp[i][j]=dp[i][j-1]; 
			if (i>=w[j]) {
				dp[i][j]=max(dp[i-w[j]][j-1]+k[j],dp[i][j]);
			}			
		}
	
	cout<<dp[s][n];
}
