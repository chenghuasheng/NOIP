#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;
const int MAXN=100000;
int n;
int a[MAXN+1],b[MAXN+1];
int dp[MAXN+1];
int map[MAXN+1];
int f[MAXN+1];
int len;

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        map[a[i]]=i;
    }
    for(int i=1;i<=n;i++) {
        cin>>b[i];
        f[i]=INT_MIN;
    }
    len=0;
    f[0]=0;
    for(int i=1;i<=n;i++){
        if (map[b[i]]>f[len]) f[++len]=map[b[i]];
        else {
          int k=upper_bound(f,f+len+1,map[b[i]])-f;
            f[k]=map[b[i]];
        }
    }
    cout<<len;    
}