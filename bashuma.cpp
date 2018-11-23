//http://www.joyoi.cn/problem/tyvj-1541 °ËÊýÂë 
#include<iostream>
#include<fstream>
#include<queue>
#include<set>
using namespace std;
ifstream fin("bashuma.in");
ofstream fout("bashuma.out");
struct State{
	string qipan;
	int zeroPos;
	int deep;
};
set<string> visitedQipan;
State sourceState,targetState;
queue<State> Q;
int minDeep;
void move(State &s,int oldPos,int newPos)
{
	char c;
	c=s.qipan[oldPos];
	s.qipan[oldPos]=s.qipan[newPos];
	s.qipan[newPos]=c;
	s.zeroPos=newPos;
}
bool same(State s1,State s2){
	if (s1.zeroPos!=s2.zeroPos) return false;
	for(int i=0;i<9;i++) if (s1.qipan[i]!=s2.qipan[i]) return false;
	return true;
}
void bfs(){
	Q.push(sourceState);
	while(!Q.empty()){
		State cur=Q.front();
		Q.pop();
		if (same(cur,targetState)) {
			minDeep=cur.deep;
			break;
		}else{
			int newPos;
			newPos=cur.zeroPos-3;
			if (newPos>=0){
				State newState=cur;
				move(newState,cur.zeroPos,newPos);
				newState.deep=cur.deep+1;
				if (visitedQipan.find(newState.qipan)==visitedQipan.end()){
					Q.push(newState);
					visitedQipan.insert(newState.qipan);
				}		
			}
			newPos=cur.zeroPos+3;
			if (newPos<=8){
				State newState=cur;
				move(newState,cur.zeroPos,newPos);
				newState.deep=cur.deep+1;
				if (visitedQipan.find(newState.qipan)==visitedQipan.end()){
					Q.push(newState);
					visitedQipan.insert(newState.qipan);
				}
			}
			if (cur.zeroPos % 3!=0) {
				State newState=cur;
				newPos=cur.zeroPos-1;
				move(newState,cur.zeroPos,newPos);
				newState.deep=cur.deep+1;
				if (visitedQipan.find(newState.qipan)==visitedQipan.end()){
					Q.push(newState);
					visitedQipan.insert(newState.qipan);
				}
			}
			if ((cur.zeroPos+1)% 3!=0){
				State newState=cur;
				newPos=cur.zeroPos+1;
				move(newState,cur.zeroPos,newPos);
				newState.deep=cur.deep+1;
				if (visitedQipan.find(newState.qipan)==visitedQipan.end()){
					Q.push(newState);
					visitedQipan.insert(newState.qipan);
				}
			}	
		}	
	}
}

int main(){
	fin>>sourceState.qipan;
	for(int i=0;i<9;i++) if (sourceState.qipan[i]=='0') sourceState.zeroPos=i;
	sourceState.deep=0;
	targetState.qipan="123804765";
	for(int i=0;i<9;i++) if (targetState.qipan[i]=='0') targetState.zeroPos=i;
	bfs();
	cout<<minDeep<<endl;
}
	
