#include <iostream>
#include <cstdio>
using namespace std;
const int MAXN=1000000;
const int MAXK=64;
unsigned long long a[MAXN+1];
unsigned long long n,m;
int c,k;
bool has[MAXK+1];
int conbit;
int qindanbit;

int main(){
    scanf("%d %d %d %d",&n,&m,&c,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=m;i++){
        int p,q;
        scanf("%d %d",&p,&q);
        if (!has[p]){
            conbit++;
            has[p]=true;
        }
    }
    unsigned long long total=0;
    for(int i=1;i<=n;i++) total|=a[i];
    int i=0;
    while(i<k){
        int flag=(total>>i)&1;
        if (flag==1&&has[i]) qindanbit++;
        i++;
    }
    int bitinc=conbit-qindanbit;
    unsigned long long x=1;
    unsigned long long sum=(x<<(k-bitinc));
    unsigned long long ans=sum-n;
    cout<<bitinc<<endl;
    cout<<sum<<endl;
    printf("%llu",ans);
}