//»¨µê³÷´°£ºhttp://www.joyoi.cn/problem/tyvj-1124 
#include<iostream> 
#include<fstream>
using namespace std;
ifstream fin("flower.in");
ofstream fout("flower.out");

int f,v;
int value[101][101];
int dp[101][101];
int pos[101][101];

void printPos(int i,int j){
	int k=pos[i][j];
	if (k>1&&j>1){
		printPos(k-1,j-1);
	}
	fout<<k<<" ";
}
int main(){
	fin>>f>>v;
	for(int i=1;i<=f;i++)
		for(int j=1;j<=v;j++)
			fin>>value[i][j];
	
	for(int i=1;i<=v;i++)
		for(int j=1;j<=i;j++){
			dp[i][j]=dp[i-1][j-1]+value[j][i];
			pos[i][j]=i;
			if (j<=i-1&&dp[i-1][j]>=dp[i][j]){
				dp[i][j]=dp[i-1][j];
				pos[i][j]=pos[i-1][j];
			} 
		}
			
	fout<<dp[v][f]<<endl;
	printPos(v,f);
		
}
