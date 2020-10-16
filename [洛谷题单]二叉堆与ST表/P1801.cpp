#include <iostream>
#include <queue>
using namespace std;
const int MAXN=200000;
int a[MAXN+10],u[MAXN+10];
int n,m;
priority_queue<int>  maxheap;
priority_queue<int,vector<int>,greater<int> > minheap;

int main(){
    cin>>m>>n;
    for(int i=0;i<m;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>u[i];

    int maxheap_cursize=0;
    int maxheap_limitsize=0;
    int uindex=0;
    for(int i=0;i<m;i++){
        //cout<<":"<<a[i]<<endl;
        if (maxheap_limitsize==0) minheap.push(a[i]);
        else {
            if (a[i]>=minheap.top()) minheap.push(a[i]);
            else {
                if (maxheap_cursize<maxheap_limitsize) {
                    maxheap.push(a[i]);
                    maxheap_cursize++;
                }else if (a[i]<maxheap.top()){
                    minheap.push(maxheap.top());
                    maxheap.pop();
                    maxheap.push(a[i]);
                }else minheap.push(a[i]);
            }
        }
        while ((i+1)==u[uindex]){
            while(maxheap_cursize<maxheap_limitsize){
                maxheap.push(minheap.top());
                minheap.pop();
                maxheap_cursize++;
            }
            cout<<minheap.top()<<endl;
            maxheap_limitsize++;
            uindex++;
        }
    }
}