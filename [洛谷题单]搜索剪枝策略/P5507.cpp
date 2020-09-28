#include <iostream>
#include <queue>

using namespace std;
struct State{
    char buttons[13]={0};//按钮状态0—3
    char actions[20]={0};//动作串
    int step;
    int dist;
    bool operator<(const State other)const{
        return (dist/2+step)>(other.dist/2+other.step);
    }
};
int calc_dist(State s){
    int ret=0;
    for(int i=1;i<=12;i++){
        ret+=(4-s.buttons[i])%4;
    }
    return ret;
}
int gethash(State s){
    int ret=0;
    for(int i=1;i<=12;i++){
        int p=(i-1)*2;
        ret+=s.buttons[i]*(1<<p);
    }
    return ret;
}
int a[13][4];
bool visited[20000000];
priority_queue<State> priQueue;
State start;
int main(){
    for(int i=1;i<=12;i++){
        int si;
        cin>>si;
        start.buttons[i]=si-1;
        for(int j=0;j<4;j++) cin>>a[i][j];
    }
    start.step=0;
    start.dist=calc_dist(start);
    int key=gethash(start);
    visited[key]=true;
    priQueue.push(start);
    while(!priQueue.empty()){
        State cur=priQueue.top();
        priQueue.pop();
        if (cur.dist==0){
            cout<<cur.step<<endl;
            for(int i=1;i<=cur.step;i++) cout<<((int)cur.actions[i])<<" ";
            return 0;
        }else {
            for(int i=1;i<=12;i++){
                State next=cur;
                int w=a[i][next.buttons[i]];
                next.buttons[i]=(++next.buttons[i])%4;
                next.buttons[w]=(++next.buttons[w])%4;
                int key=gethash(next);
                if (!visited[key]){
                    next.step++;
                    next.actions[next.step]=i;
                    next.dist=calc_dist(next);
                    priQueue.push(next);
                    visited[key]=true;
                }
            }
        }
    }
}
