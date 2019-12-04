#include <iostream>
using namespace std;
const int MAXN=64;
int n;
unsigned long long k;
int ans[MAXN+1];
unsigned long long mi2[MAXN+1];
void dfs(int i,int j,int dir){
    if (i==0){
        return;
    }else {
        if (dir==0){
            if (k>=mi2[i-1]){
                ans[i]=1;
                k=k-mi2[i-1];
                dfs(i-1,k,1);
            }else {
                ans[i]=0;
                dfs(i-1,k,0);
            }
        }else {
            if (k<mi2[i-1]){
                ans[i]=1;
                dfs(i-1,k,0);
            }else {
                ans[i]=0;
                k=k-mi2[i-1];
                dfs(i-1,k,1);
            }
        }
    }
}
int main(){
    cin>>n>>k;
    mi2[0]=1;
    for(int i=1;i<=n;i++) mi2[i]=mi2[i-1]*2;
    dfs(n,k,0);
    for(int i=n;i>=1;i--) cout<<ans[i];
}