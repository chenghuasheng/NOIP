#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;
const int MAXN=1000000;
struct Snake{
    int id;
    int a;
    bool operator >(const Snake other)const{
        return (a>other.a)||(a==other.a&&id>other.id);
    }
    bool operator <(const Snake other)const{
        return (a<other.a)||(a==other.a&&id<other.id);
    }
};
Snake snakes[MAXN+1];
priority_queue<Snake> maxHeap;
priority_queue<Snake,vector<Snake>,greater<Snake> > minHeap;
int t,n,k;
int dowith(){
    int c=0;
    while(1){
        Snake maxs=maxHeap.top();
        Snake mins=minHeap.top();
        minHeap.pop();c++;
        Snake secmins=minHeap.top();
        //cout<<"max="<<maxs.a<<" min="<<mins.a<<" secmins="<<secmins.a<<endl;
        maxs.a=maxs.a-mins.a;
        if (maxs>secmins||c==n-1) {
            maxHeap.pop();
            maxHeap.push(maxs);
            minHeap.push(maxs);
        }else break;
    }
    return c-1;
}
void clear(){
    while(!maxHeap.empty()) maxHeap.pop();
    while(!minHeap.empty()) minHeap.pop();
}
int main(){
    scanf("%d",&t);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&snakes[i].a);
        maxHeap.push(snakes[i]);
        minHeap.push(snakes[i]);
    }
    printf("%d\n",n-dowith());
    for(int i=1;i<t;i++){
        scanf("%d",&k);
        for(int j=1;j<=k;j++){
            int x,y;
            scanf("%d %d",&x,&y);
            snakes[x].a=y;
        }
        clear();
        for(int i=1;i<=n;i++){
            maxHeap.push(snakes[i]);
            minHeap.push(snakes[i]);
        }
        printf("%d\n",n-dowith());
    }
}