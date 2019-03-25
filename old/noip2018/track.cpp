#include<iostream>
#include<fstream> 
#include<vector>
#include<algorithm> 
#include<cstring> 
const int MAXDIS=20000;
using namespace std;
ifstream fin("track8.in");
//ofstream fout("track.out");
struct Edge{
	long to;
	int dis;
};
long n,m;
vector<Edge> G[50001];
long sumDis=0;
long minDis=MAXDIS;
long curLenForTrack;
long dp[50001];
long restMaxLens[50001];
long parent[50001];

long check(vector<long> &lens,long left,long right,long minVal){
	long ret=lens.size();
	while(left<=right){
		long mid=(left+right)/2;
		long mid1=mid;
		while(mid1>left&&lens[mid1]==0) mid1--; 
		if (lens[mid1]>=minVal) {
			if (mid1<ret) ret=mid1;
			right=mid1-1;
		}else left=mid+1;
	}
	return ret;
}
void dfs(long k){
	vector<long> lens;
	for(long i=0;i<G[k].size();i++){
		Edge e=G[k][i];
		if (e.to!=parent[k]) {
			parent[e.to]=k;
			dfs(e.to);
			dp[k]+=dp[e.to];
			long newRestLen=restMaxLens[e.to]+e.dis;
			if (newRestLen>=curLenForTrack) dp[k]++;
			else lens.push_back(newRestLen);
		}
	}
	long s=lens.size();
	if (s>0){
		if (s>1) sort(lens.begin(),lens.begin()+s);
		for(long i=0;i<s;i++){
			if (lens[i]==0) continue;
			long j=check(lens,i+1,s-1,curLenForTrack-lens[i]);
			if (j<s){
				dp[k]++;
				lens[i]=0;
				lens[j]=0; 
			}else restMaxLens[k]=lens[i];
		}		
	}
}

int main(){
	fin>>n>>m;
	for(long i=0;i<n-1;i++){
		long a,b;
		int c;
		fin>>a>>b>>c;
		Edge e1={b,c};
		G[a].push_back(e1);
		Edge e2={a,c};
		G[b].push_back(e2);
		sumDis+=c;
		if (c<minDis) minDis=c;
	}
	long left=minDis;
	long right=sumDis/m;
	long ans=0;
	while(left<=right){
		long mid=(left+right)/2;
		curLenForTrack=mid;
		memset(dp,0,sizeof(dp));
		memset(restMaxLens,0,sizeof(restMaxLens));
		memset(parent,0,sizeof(parent));
		dfs(1);
		//cout<<"curLen="<<mid<<" dp="<<dp[1]<<endl;
		if (dp[1]<m) right=mid-1;
		else {
			ans=curLenForTrack;
			left=mid+1;
		}
	}
	cout<<ans<<endl;
}
