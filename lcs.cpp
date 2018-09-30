//最长公共子序列：http://www.joyoi.cn/problem/tyvj-1050
#include <iostream>
#include <fstream>
#include<string>
using namespace std;
ifstream fin("lcs.in");
ofstream fout("lcs.out");
string a,b;
int dp[2001][2001];
int la,lb;
int main(){
	fin>>a>>b;
	la=a.size();
	lb=b.size();
	a=" "+a;
	b=" "+b; 
	for(int i=1;i<=la;i++)
		for(int j=1;j<=lb;j++){
			if (a[i]==b[j]) dp[i][j]=dp[i-1][j-1]+1;
			else {
				dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
			}
		}
	
	fout<<dp[la][lb]<<endl;	
}

