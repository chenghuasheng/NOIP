#include<iostream>
#include<queue>
using namespace std;
const int MAXN=100000;
int a[MAXN+1],b[MAXN+1];
int c[MAXN+1];
int n;
priority_queue<int> maxheap;
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0;i<n;i++) cin>>b[i];
    int s=0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++){
            int sum=a[i]+b[j];
            if (s<n){
                maxheap.push(sum);
                s++;
            }else {
                if (sum>=maxheap.top()) break;
                else{
                    maxheap.pop();
                    maxheap.push(sum);
                }
            }
        }
    int i=0;
    while(!maxheap.empty()){
        c[n-1-i]=maxheap.top();
        maxheap.pop();
        i++;
    }
    for(int i=0;i<n;i++) cout<<c[i]<<' ';

}
