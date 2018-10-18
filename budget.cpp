//金明的预算方案：http://www.joyoi.cn/problem/tyvj-1057
#include<iostream>
#include<fstream>
#include <vector>
using namespace std;
ifstream fin("budget.in");
ofstream fout("budget.out");

int n,m;
int v[61],p[61],q[61];
int dp[32001][61];
vector<int>  acc[61];

int main(){
	fin>>n>>m;
	for(int i=1;i<=m;i++) { 
		fin>>v[i]>>p[i]>>q[i];
		if (q[i]>0) {
			acc[q[i]].push_back(i);
		}
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			dp[i][j]=dp[i][j-1];
			if (q[j]>0) continue;
			if (i>=v[j]){
				dp[i][j]=max(dp[i][j],v[j]*p[j]+dp[i-v[j]][j-1]);
				int size=acc[j].size();
				if (size>0){
					int a=acc[j][0];
					int ts;
					int vs=v[j]+v[a];
					if (i>=vs){ 	
						ts=v[j]*p[j]+v[a]*p[a];
						dp[i][j]=max(dp[i][j],ts+dp[i-vs][j-1]);
					}
					if (size>1){
						int b=acc[j][1];
						vs=v[j]+v[b];
						if (i>=vs){ 	
							ts=v[j]*p[j]+v[b]*p[b];
							dp[i][j]=max(dp[i][j],ts+dp[i-vs][j-1]);
						}
						vs=v[j]+v[a]+v[b]; 
						if (i>=vs){
							ts=v[j]*p[j]+v[a]*p[a]+v[b]*p[b];
							dp[i][j]=max(dp[i][j],ts+dp[i-vs][j-1]);
						}
					}
				}
			}
			
			
		}
	fout<<dp[n][m];
}
