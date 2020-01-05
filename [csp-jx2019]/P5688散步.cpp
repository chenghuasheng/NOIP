#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN=200000;
const int MAXL=1000000000;

int person_pos[MAXN+1],exit_pos[MAXN+2];
int dir[MAXN+1],limit[MAXN+1];
int next_exit[MAXN+2],prev_exit[MAXN+2];
struct Node{
    int person;
    int exit;
    int distance;
    bool operator < (const Node other) const{
        if (distance==other.distance){
            if (exit==other.exit) return person>other.person;
            else return exit>other.exit;
        }else return distance>other.distance;
    }
};
priority_queue<Node> minQueue;
int leaved[MAXN+1];
int n,m,l;
int find_nearest_exit(int i){
    int pos=person_pos[i];
    int left=1;
    int right=m+1;
    while (left<right){
        int mid=(left+right)/2;
        if (exit_pos[mid]>pos) right=mid;
        else if (exit_pos[mid+1]<=pos) left=mid+1;
        else {
            left=mid;
            break;
        } 
    }
    if (pos==exit_pos[left]) return left;
    else {
        if (dir[i]==0) return (left % m)+1;
        else return left;
    }
}
int find_next_exit(int i,int j){
    int oldj=j;
    do {
        if (dir[i]==0) j=next_exit[j];
        else j=prev_exit[j];
        if (j==oldj){
            return -1;
        }
        oldj=j;
    }while(limit[j]<=0);
    return j; 
}
int main(){
    cin>>n>>m>>l;
    exit_pos[1]=0;exit_pos[m+1]=l;
    for(int i=2;i<=m;i++) cin>>exit_pos[i];
    for(int i=1;i<=m;i++) {
        cin>>limit[i];
        prev_exit[i]=(i-2+m) % m + 1;
        next_exit[i]= i % m + 1;
    }
    for(int i=1;i<=n;i++) cin>>dir[i]>>person_pos[i];
    for(int i=1;i<=n;i++){
        int j=find_nearest_exit(i);
        int dis;
        if (dir[i]==0){
            dis=(exit_pos[j]-person_pos[i]+l) % l;
        }else {
            dis=(person_pos[i]-exit_pos[j]+l) % l;
        }
        Node nd={i,j,dis};
        minQueue.push(nd);
    }
    while(!minQueue.empty()){
        Node cur=minQueue.top();
        minQueue.pop();
        int i=cur.person;
        int j=cur.exit;
        int dis;
        if (limit[j]>0){
            leaved[i]=j;
            limit[j]--;
            if (limit[j]==0){
                next_exit[prev_exit[j]]=next_exit[j];
                prev_exit[next_exit[j]]=prev_exit[j];
            }
        }else {
            int newj=find_next_exit(i,j);
            if (newj>0){
                cur.exit=newj;
                if (dir[i]==0){
                    cur.distance=(exit_pos[newj]-person_pos[i]+l) % l;
                }else {
                    cur.distance=(person_pos[i]-exit_pos[newj]+l) % l;
                }
                minQueue.push(cur);
            }
        }
    }    
    
    long long ans=0;
    for(int i=0;i<=n;i++) ans^=(1LL*i*leaved[i]);
    cout<<ans;
}
