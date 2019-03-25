//最大的算式 http://www.joyoi.cn/problem/tyvj-1045
#include<iostream>
#include<fstream>
using namespace std;
ifstream fin("equation.in");
ofstream fout("equation.out");

int N,K;
int num[101];
int dp[101][100];
int sum[101];
int main(){
	fin>>N>>K;
	for(int i=1;i<=N;i++) fin>>num[i];
	for(int i=1;i<=N;i++) sum[i]=sum[i-1]+num[i];
	
	for(int i=1;i<=N;i++) dp[i][0]=sum[i];
	
	for(int k=1;k<N;k++){
		for(int i=1;i<=N;i++){
			for(int p=1;p<i;p++) dp[i][k]=max(dp[i][k],dp[p][k-1]*(sum[i]-sum[p])); 
		}
	}
	fout<<dp[N][K]<<endl;
}
