//ÂÃÐÐ https://www.luogu.org/problemnew/show/P5022
#include <iostream>
#include <fstream>
#include <vector> 
#include <cstring>
#include <algorithm> 

using namespace std;
ifstream fin("travel16.in"); 
//ofstream fout("travel.out");
int n,m;
struct Edge{
	int from;
	int to;
	bool operator<(const Edge& other) const{
		return from<other.from||(from==other.from&&to<other.to);
	}
};
vector<int> G[5001];
vector<Edge> edges;
bool flag[5001];
vector<int> result;
vector<int> temp;
void dfs(int u){
	result.push_back(u);
	flag[u]=true;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if (!flag[v]) dfs(v);	
	}
}
void dfs(int u,int k){
	temp.push_back(u);
	flag[u]=true;
	for(int i=0;i<G[u].size();i++){
		int v=G[u][i];
		if ((u==edges[k].from&&v==edges[k].to)
			||(u==edges[k].to&&v==edges[k].from)) continue;
		if (!flag[v]) dfs(v,k);	
	}
}
int main(){
	fin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v;
		fin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		Edge e;
		u<v?e={u,v}:e={v,u};
		edges.push_back(e);
	}
	for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].begin()+G[i].size());
	if (m<n) {
		memset(flag,false,sizeof(flag));
		dfs(1);
	}else {
		sort(edges.begin(),edges.begin()+m);
		for(int i=0;i<n;i++) result.push_back(n);
		bool finished=false;
		for(int i=0;i<m;i++){
			cout<<edges[i].from<<"->"<<edges[i].to<<endl;
			
			memset(flag,false,sizeof(flag));
			temp.clear();
			dfs(1,i);
			if (temp.size()<n) continue;
			bool better=false;
			for(int i=0;i<n;i++){
				if(better) result[i]=temp[i];
				else {
					if (temp[i]>result[i]) {
						//finished=true;
						break;
					}
					else if (temp[i]<result[i]) {
						result[i]=temp[i];
						better=true;
					}
				}
			}
			//if (finished) break;	
		}
	}
	
	for(int i=0;i<result.size();i++) cout<<result[i]<<" ";
	cout<<endl;
}
