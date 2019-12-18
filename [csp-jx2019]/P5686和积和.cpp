#include <iostream>
using namespace std;
const int MOD=1000000007;
const int MAXN=500000;
long long a[MAXN+1],b[MAXN+1];
long long sa[MAXN+1],sb[MAXN+1];//从1向n的累加
long long totalSa[MAXN+1],totalSb[MAXN+1],totalSaSb[MAXN+1];//从n向1的累加
int n;
long long ans;
long long add(long long a,long long b){
    a=a%MOD;
    b=b%MOD;
    return (a+b)%MOD;
}
long long mul(long long a,long long b){
    a=a%MOD;
    b=b%MOD;
    return (a*b)%MOD;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        sa[i]=(sa[i-1]+a[i]) % MOD;
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
        sb[i]=(sb[i-1]+b[i]) % MOD;
    }
    totalSa[n]=sa[n];
    totalSb[n]=sb[n];
    totalSaSb[n]=mul(sa[n],sb[n]);
    for(int i=n-1;i>0;i--){
        totalSa[i]=add(totalSa[i+1],sa[i]);
        totalSb[i]=add(totalSb[i+1],sb[i]);
        totalSaSb[i]=add(totalSaSb[i+1],mul(sa[i],sb[i]));
    }
    for(int i=1;i<=n;i++){
        long long t1=mul(sb[i-1],totalSa[i]);
        long long t2=mul(sa[i-1],totalSb[i]);
        long long t3=mul((n-i+1),mul(sa[i-1],sb[i-1]));
        ans=(ans+add(totalSaSb[i],t3)+(MOD-add(t1,t2)))%MOD;
    }
    cout<<ans;
}
