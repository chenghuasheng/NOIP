#include<iostream> 
using namespace std;
int pos[4];
int ans=0;
bool confict(int i,int j){
	for(int k=0;k<i;k++){
		int x1=pos[k] / 4;
		int x2=j / 4;
		int y1=pos[k] % 4;
		int y2=j % 4;
		if (x1==x2) return true;
		if (y1==y2) return true;
		if (y2-y1==x2-x1) return true;
		if (y2-y1==x1-x2) return true;
	}
	return false;
}
void dfs(int i,int start){
	if (i>=4) {
		ans++;
		return;
	}
	for(int j=start;j<16;j++){
		if (confict(i,j)) continue;
		pos[i]=j;
		dfs(i+1,j+1);
	} 
}
int main(){
	ans=0;
	dfs(0,0); 
	cout<<ans<<endl;
}
