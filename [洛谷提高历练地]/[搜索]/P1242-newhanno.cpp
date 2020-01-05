#include <iostream>
#include <queue>


using namespace std;
const int MAXN=45;
const int MAXK=10000;

struct Stack{
    int data[MAXN+1]={0};
    int top=0;
    void push(int x){
        data[top]=x;
        top++;
    }
    int get_top(){
        if (top>0) return data[top-1];
        else return 0;
    }
    void pop(){
        if (top>0) top--;
    }
    int count(){
        return top;
    }
    bool issame(const Stack other){
        if (top!=other.top) return false;
        else {
            for(int i=0;i<top;i++)
                if (data[i]!=other.data[i]) return false;
            return true;
        }
    }
};

char name[3]={'A','B','C'};

struct Status{
    Stack ta[3];
    int level=0;
    bool issame(const Status other){
        return (ta[0].issame(other.ta[0])&&
        ta[1].issame(other.ta[1])&&
        ta[2].issame(other.ta[2]));
    }
    bool canmove(int from,int to){
        int top1=ta[from].get_top();
        int top2=ta[to].get_top();
        return (top1&&(!top2||top1<=top2));
    }
    void move(int from,int to){
        int x=ta[from].get_top();
        ta[from].pop();
        ta[to].push(x);
        cout<<"move "<<x<<" from "<<name[from]<<" to "<<name[to]<<endl;
    }
};
void read(Status &s){
    for(int i=0;i<3;i++){
        int t;
        cin>>t;
        for(int j=0;j<t;j++){
            int a;
            cin>>a;
            s.ta[i].push(a);
        }
    } 
}
Status source,dest;
int n;
queue<Status> q;
int main(){
   cin>>n;
   read(source);
   read(dest);
   source.level=0;
   q.push(source);
   while(!q.empty()){
       Status cur=q.front();
       q.pop();
       if (cur.issame(dest)){
           cout<<cur.level;
           break;
       }else {
           for(int from=0;from<3;from++)
            for(int to=0;to<3;to++){
                if (from!=to&&cur.canmove(from,to)){
                    Status next=cur;
                    next.move(from,to);
                    next.level++;
                    q.push(next);
                }
            }
       }
   }
}