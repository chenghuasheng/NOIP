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
struct Hnum{
    int e[50]={0};
    int s=1;
    void set(int x){
        s=0;
        while(x>0){
            e[s]=x&1;
            x=x>>1;
            s++;
        }
    }
    void mult(int k){
        int c=0;
        for(int i=0;i<s;i++){
            e[i]=e[i]*k+c;
            c=e[i]/10;
            e[i]=e[i]%10;
        }
        if (c>0) {
            e[s]=c;
            s++;
        }
    }
    void sub(Hnum other){
        int l=max(s,other.s);
        int c=0;
        for(int i=0;i<l;i++){
            e[i]=e[i]-other.e[i]+c;
            if (e[i]<0){
                e[i]=10-e[i];
                c=-1;
            }else c=0;
        }
    }
    void output(){
        for(int i=s-1;i>=0;i--) printf("%d",e[i]);
    }
};
Hnum mi2;
Hnum hn;
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
    if (k-bitinc>=64){
        mi2.set(1);
        for(int i=1;i<=k-bitinc;i++) mi2.mult(2);
        hn.set(n);
        mi2.sub(hn);
        mi2.output();
    }else {
        unsigned long long x=1;
        unsigned long long sum=(x<<(k-bitinc));
        unsigned long long ans=sum-n;
        printf("%llu",ans);
    }
}