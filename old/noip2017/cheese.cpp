//http://www.joyoi.cn/problem/noip2017-cheese noip2017ฤฬภา 
#include<iostream>
#include<fstream>
#include<stack>
#include<algorithm>
#include<cstring>
using namespace std;
ifstream fin("cheese.in");
ofstream fout("cheese.out");
struct Point{
	long x,y,z;
};

int T;
int n;
long h,r;
Point ballCenters[1000];
bool visited[1000];

bool lessCmp(Point a,Point b){
	return a.z<b.z;
}
bool can_arrive(int i,int j){
	long detaX=ballCenters[i].x-ballCenters[j].x;
	long detaY=ballCenters[i].y-ballCenters[j].y;
	long detaZ=ballCenters[i].z-ballCenters[j].z;
	long long dis2=detaX*detaX+detaY*detaY+detaZ*detaZ;
	if (dis2<=4*r*r) return true;
	else return false;
}
int main(){
	fin>>T;
	for(int i=0;i<T;i++){	
		fin>>n>>h>>r;
		for(int j=0;j<n;j++){
			fin>>ballCenters[j].x>>ballCenters[j].y>>ballCenters[j].z;
		}
		sort(ballCenters,ballCenters+n,lessCmp);
		stack<int> S;  
		
		memset(visited,false,sizeof(visited));
		for(int j=0;j<n;j++){
			if (ballCenters[j].z<=r) {
				S.push(j);
				visited[j]=true;
			}
		}
		bool can=false;
		while(!S.empty()){
			int cur=S.top();
			S.pop();
			if (ballCenters[cur].z+r>=h){
				can=true;
				break;
			}else {
				for(int j=cur+1;j<n;j++){
					if (visited[j]) continue;
					if (ballCenters[cur].z+2*r<ballCenters[j].z) break;
					if (can_arrive(cur,j)) {
						S.push(j);
						visited[j]=true;
					}
				}
				for(int j=cur-1;j>=0;j--){
					if (visited[j]) continue;
					if (ballCenters[cur].z-2*r>ballCenters[j].z) break;
					if (can_arrive(cur,j)) {
						S.push(j);
						visited[j]=true;
					}
				}
			}
		}
		if (can) fout<<"Yes"<<endl;
		else fout<<"No"<<endl;
	}
}
