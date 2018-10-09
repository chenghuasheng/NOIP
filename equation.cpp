//最大的算式 http://www.joyoi.cn/problem/tyvj-1045
#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("equation.in");
ofstream fout("equation.out");

int N,K;
int num[101];
int dp[101][101][100];

int main(){
	fin>>N>>K;
	for(int i=1;i<=N;i++) fin>>num[i];
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j++) dp[i][j][0]=dp[i][j-1][0]+num[j];
	
	for(int k=1;k<N;k++){
		for(int l=k;l<N;l++)
			for(int i=1;i<=N;i++){
				int j=i+l;
				if (j>N) break;
				for(int p=i;p<=j-k;p++) dp[i][j][k]=max(dp[i][j][k],dp[i][p][0]*dp[p+1][j][k-1]) ;
			}
	}
	fout<<dp[1][N][K]<<endl;
}
