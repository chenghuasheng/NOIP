#include <iostream>
using namespace std;
const int MAXN=500000;
int n,type;
int a[MAXN+1];
unsigned long long dp[MAXN+1],last[MAXN+1];
unsigned long long sum[MAXN+1];

int main(){
	cin>>n>>type;
	for(int i=1;i<=n;i++) cin>>a[i];
	sum[0]=0;
	for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
	
	dp[0]=0;
	last[0]=0;
	for(int i=1;i<=n;i++){
		for(int j=i;j>=1;j--){
			if (sum[i]-sum[j-1]>=last[j-1]) {
				dp[i]=dp[j-1]+(sum[i]-sum[j-1])*(sum[i]-sum[j-1]);
				last[i]=sum[i]-sum[j-1];
				break;
			}
		}
	}
	cout<<dp[n];
}