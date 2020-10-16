#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
const int MAXN=150000;
struct Task{
    int t1;
    int t2;
    bool operator<(const Task other)const{
        return t2<other.t2;
    }
};
Task tasks[MAXN+1];
priority_queue<int> heap;
int sumt;
int n,ans;

int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>tasks[i].t1>>tasks[i].t2;
    }
    sort(tasks,tasks+n);
    sumt=0;
    ans=0;
    for(int i=0;i<n;i++){
        if (sumt+tasks[i].t1<=tasks[i].t2){
            sumt+=tasks[i].t1;
            ans++;
            heap.push(tasks[i].t1);
        }else {
            if (tasks[i].t1<heap.top()){
                sumt-=heap.top();
                sumt+=tasks[i].t1;
                heap.pop();
                heap.push(tasks[i].t1);
            }
        }
    }
    cout<<ans;
    //system("pause");
}