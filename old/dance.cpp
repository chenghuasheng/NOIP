//没有上司的舞会： http://www.joyoi.cn/problem/tyvj-1052
#include<iostream> 
#include<fstream>
#include<vector>
using namespace std;
ifstream fin("dance.in");
ofstream fout("dance.out");
int n;
int happy[3001];
vector<int> tree[3001];
int dp[3001][2];
bool visited[3001];
int max_happy;

void tree_dp(int i){
	if (visited[i]) return;
	int childNum=tree[i].size();
	if (childNum>0){
		int s1=0,s2=0;
		for(int j=0;j<childNum;j++){
			int k=tree[i][j];
			tree_dp(k);
			s1=s1+dp[k][0];
			s2=s2+max(dp[k][0],dp[k][1]);
		}
		dp[i][1]=s1+happy[i];
		dp[i][0]=s2;
	}else{
		dp[i][0]=0;
		dp[i][1]=happy[i];
	}
	visited[i]=true;
}
int main(){
	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>happy[i];
	int a,b=0;
	do {
		fin>>a>>b;
		if (b>0&&a>0) tree[b].push_back(a);
		else break;
	}while(true);
	
	for(int i=1;i<=n;i++) {
		tree_dp(i);
		max_happy=max(max_happy,max(dp[i][0],dp[i][1]));
	}
	fout<<max_happy;
}
