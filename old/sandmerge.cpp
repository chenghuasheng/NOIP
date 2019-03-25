#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("sandmerge.in");
ofstream fout("sandmerge.out");

int N;
int v[301];
int dp[301][301];
int vs[301][301];

int main(){
	fin>>N;
	for(int i=1;i<=N;i++) fin>>v[i];
	
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j++) vs[i][j]=vs[i][j-1]+v[j];
	
	for(int k=1;k<N;k++)
		for(int i=1;i<=N;i++){
			int j=i+k;
			if (j>N) break;
			dp[i][j]=dp[i][i]+dp[i+1][j]+vs[i][i]+vs[i+1][j];
			for(int m=i+1;m<j;m++) dp[i][j]=min(dp[i][j],dp[i][m]+dp[m+1][j]+vs[i][m]+vs[m+1][j]);
		}
	fout<<dp[1][N]<<endl; 
}
