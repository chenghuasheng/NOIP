#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN=100000;
const int MAXPOW=20;
int a[MAXN+1];
int maxv[MAXN+1][MAXPOW+1];
int n,m;
int query(int l,int r){
    int ret=0;
    for(int j=MAXPOW;j>=0;j--){
        if (l+(1<<j)-1<=r) {
            ret=max(ret,maxv[l][j]);
            l=l+(1<<j);
        }
    }
    return ret;
}
int main(){
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) maxv[i][0]=a[i];
    for(int j=1;j<=MAXPOW;j++)
        for(int i=1;i<=n+1-(1<<j);i++){
            maxv[i][j]=max(maxv[i][j-1],maxv[i+(1<<(j-1))][j-1]);
        }
    for(int i=1;i<=m;i++){
        int l,r;
        scanf("%d %d",&l,&r);
        printf("%d\n",query(l,r));
    }
}