#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
const int MAXN=200000;
const int MAXL=1000000000;

int person_pos[MAXN+1],dir[MAXN+1];
int exit_pos[MAXN+1],limit[MAXN+1];
struct Node{
    int person;
    int exit;
    int distance;
    bool operator < (const Node other) const{
        if (distance==other.distance&&exit==other.exit)
            return person>other.person;
        else return distance>other.distance;
    }
};
priority_queue<Node> minQueue;
int leaved[MAXN+1];

int n,m,l;
int main(){
    cin>>n>>m>>l;
    for(int i=2;i<=m;i++) cin>>exit_pos[i];
    for(int i=1;i<=m;i++) cin>>limit[i];
    for(int i=1;i<=n;i++) cin>>dir[i]>>person_pos[i];
    for(int i=1;i<=n;i++){
        int mindis=MAXL;
        int minj=0;
        if (dir[i]==0){
            for(int j=m;j>=1;j--){
                int dis=(exit_pos[j]-person_pos[i]+l) % l;
                if (dis<mindis) {
                    mindis=dis;
                    minj=j;
                }
                else break;
            }
        }else {
            for(int j=1;j<=m;j++){
                int dis=(person_pos[i]-exit_pos[j]+l) % l;
                if (dis<mindis) {
                    mindis=dis;
                    minj=j;
                }
                else break;
            }
        }
        Node nd={i,minj,mindis};
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
        }else {
            bool hasNew=true;
            if (dir[i]==0){
                do {
                    j=(j % m) +1;
                    if (j==cur.exit){
                        hasNew=false;
                        break;
                    }
                }while(limit[j]<=0);
                if (hasNew) dis=(exit_pos[j]-person_pos[i]+l) % l;
            }else {
                do {
                    j=(j-2+m) % m +1;
                    if (j==cur.exit){
                        hasNew=false;
                        break;
                    }
                }while(limit[j]<=0);
                if (hasNew) dis=(person_pos[i]-exit_pos[j]+l) % l;
            }
            if (hasNew){
                cur.exit=j;
                cur.distance=dis;
                minQueue.push(cur);
            }
        }
    }    
    
    int ans=0;
    for(int i=0;i<=n;i++) ans=ans xor(i*leaved[i]);
    cout<<ans;
}
