#include <iostream>
#include <queue>

using namespace std;
int a[13][4];
struct JiGuan{
    int button=0;
    void turn(int i){
        int t=get(i);
        int w=a[i][t];
        t=(++t)%4;
        set(i,t);
        int t1=get(w);
        t1=(++t1)%4;
        set(w,t1);
    }
    int get(int i){
        int pos=(i-1)*2;
        int flag=(1<<pos)+(1<<(pos+1));
        int si=(button&flag)>>pos;
        return si;
    }
    void set(int i,int val){
        int pos=(i-1)*2;
        int flag=(1<<pos)+(1<<(pos+1));
        int si=val<<pos;
        flag=0xffffffff-flag;
        button=(button&flag)+si;
    }
};
struct State{
    JiGuan jg;
    int step;
    int action;
    int id;
    int pid;
};
vector<State> states;
bool visited[20000000];
queue<int> qe;
State start;
int scount;
void output(int id){
   int pid=states[id].pid;
   if (pid>0) output(pid);
   cout<<states[id].action<<" "; 
}
int main(){
    for(int i=1;i<=12;i++) {
        int si;
        cin>>si; 
        start.jg.set(i,si-1);
        for(int j=0;j<4;j++) cin>>a[i][j];
    }
    start.id=scount;
    start.step=0;
    start.action=0;
    start.pid=-1;
    states.push_back(start);
    scount++;
    qe.push(start.id);
    visited[start.jg.button]=true;
    while (!qe.empty())
    {
        State cur=states[qe.front()];
        if (cur.jg.button==0) {
            cout<<cur.step<<endl;
            output(cur.id);
            return 0;
        }
        qe.pop();
        for(int i=1;i<=12;i++){
            int si=cur.jg.get(i);
            if (si==0) continue;
            JiGuan newjg=cur.jg;
            newjg.turn(i);
            if (!visited[newjg.button]){
                State next;
                next.jg=newjg;
                next.action=i;
                next.step=cur.step+1;
                next.id=scount;
                next.pid=cur.id;
                states.push_back(next);
                scount++; 
                qe.push(next.id);
                visited[newjg.button]=true;
            }
        }
    }  
}