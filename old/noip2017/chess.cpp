//∆Â≈Ã£∫http://www.joyoi.cn/problem/noip2017-chess 
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
ifstream fin("chess.in");
ofstream fout("chess.out");
int m,n;
int chess[101][101];
bool flag[101][101];
int min_cost=50000;
int costed[101][101];
 
bool reached=false;
struct offset{
	int x;
	int y;
} off[4]={{-1,0},{1,0},{0,-1},{0,1}};

void search(int x,int y,int color,int cost,bool can_magic){
	costed[x][y]=min(cost,costed[x][y]);
	if (x==m&&y==m){
		if (cost<min_cost) min_cost=cost;
		reached=true;
	}else{
		flag[x][y]=true;
		for(int i=0;i<4;i++){
			int x1=x+off[i].x;
			int y1=y+off[i].y;
			if (x1<1||x1>m||y1<1||y1>m) continue;
			if (flag[x1][y1]) continue;
			if (chess[x1][y1]!=-1){	
				int inc_cost=abs(chess[x1][y1]-color);
				if (cost+inc_cost<costed[x1][y1]) search(x1,y1,chess[x1][y1],cost+inc_cost,true);
			}else{
				if (can_magic){
					if (cost+2<=costed[x1][y1]) search(x1,y1,color,cost+2,false);
				}
			}
		}
		flag[x][y]=false;
	}
}
int main(){
	fin>>m>>n;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++) {
			chess[i][j]=-1;
			costed[i][j]=50000;
		}
	
	for(int i=1;i<=n;i++){
		int a,b,c;
		fin>>a>>b>>c;
		chess[a][b]=c;
	}
	search(1,1,chess[1][1],0,true);
	if (reached){
		fout<<min_cost;
	}else{
		fout<<-1;
	}
}

