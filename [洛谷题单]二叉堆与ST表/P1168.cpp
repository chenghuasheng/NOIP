#include <iostream>
#include <queue>
using namespace std;
const int MAXN=100000;
int a[MAXN+1];
int n;
priority_queue<int> maxheap;
priority_queue<int,vector<int>,greater<int> > minheap;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    int smin=0;
    for(int i=1;i<=n;i++){
        if (smin==0) {
            minheap.push(a[i]);
            smin++;
        }else {
            if (a[i]<=minheap.top()) {
                maxheap.push(a[i]);
            }else {
                minheap.push(a[i]);
                smin++;
            }
        }
        if (smin<((i+1)/2)){
            minheap.push(maxheap.top());
            smin++;
            maxheap.pop();
        }else if (smin>((i+1)/2)){
            maxheap.push(minheap.top());
            smin--;
            minheap.pop();
        }
        if (i%2>0) cout<<minheap.top()<<endl;
    }
}