#include<iostream>
#include<fstream> 
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
ifstream fin("pack.in");
ofstream fout("pack.out");

struct edge{
	int to;
	int dis;
};
const int MAXN=100001; 
const int INF=1000000000;

vector<edge> map[2][MAXN];
int min_dist[2][MAXN];
int dp[MAXN][55];//dp[i][j]表未从节点1到节点i中长为最短路径+j的路径条数 
int T;
int N,M,K,P;
int indeg[MAXN];
bool zero[MAXN];
bool use[MAXN];
int node[MAXN];
 
void calc_min_dist(int g,int s){//spaf算法 
	queue<int> Q;
	vector<bool> inside(N+1,false);
	min_dist[g][s]=0;
	Q.push(s);
	inside[s]=true;
	while(!Q.empty()){
		int i=Q.front();
		Q.pop();
		inside[i]=false;
		int size=map[g][i].size();
		for(int j=0;j<size;j++){
			edge e=map[g][i][j];
			if (min_dist[g][i]+e.dis<min_dist[g][e.to]) {
				min_dist[g][e.to]=min_dist[g][i]+e.dis;
				if (!inside[e.to]) {
					Q.push(e.to);
					inside[e.to]=true;
				}
			}
		}
	}
}
bool cmp(const int &a,const int &b){
	
}
bool check_zero_circle(){
	queue<int> Q;
	for(int i=1;i<=N;i++) if (zero[i]&&indeg[i]==0) Q.push(i);
	while(!Q.empty()){
		int i=Q.front();
		Q.pop();
		int size=map[0][i].size();
		for(int j=0;j<size;j++){
			edge e=map[0][i][j];
			if (zero[e.to]) {
				indeg[e.to]--;
				if (indeg[e.to]==0) Q.push(e.to);
			}
		}
	}
	for(int i=1;i<=N;i++) if (use[i]&&zero[i]&&(indeg[i]>0)) return true;
}

void init(){
	fin>>N>>M>>K>>P;
	for(int j=1;j<=N;j++) {
		map[0][j].clear();
		map[1][j].clear();
	}
	memset(zero,false,sizeof(zero));
	memset(indeg,0,sizeof(indeg));
	int a,b,c;
	for(int j=0;j<M;j++) {
		fin>>a>>b>>c; 
		edge e={b,c};
		map[0][a].push_back(e);
		edge e1={a,c};
		map[1][b].push_back(e1); 
		if (c==0) {
			zero[a]=zero[b]=true;
			indeg[b]++;
		}
	}
	for(int i=1;i<=N;i++) {
		node[i]=i;
		min_dist[0][i]=min_dist[1][i]=INF;
	}
	
}
int main(){
	fin>>T;
	for(int i=0;i<T;i++){
		
		calc_min_dist(0,1);
		calc_min_dist(1,N);	
		int dist_limit=min_dist[0][N]+K; 
		for(int i=1;i<=N;i++){
			if ((min_dist[0][i]+min_dist[1][i])>dist_limit) use[i]=false;
			else use[i]=true;
		}


		if (check_zero_circle()) fout<<-1<<endl;
		else {
			
			int res=0;
			for(int w=0;w<=K;w++) res=(res+dp[N][w]) % P;
			fout<<res; 
		}
	}
}

