#include <iostream>
#define ll long long
const ll MOD=998244353;
using namespace std;
ll n,m;
ll fast_pow(ll a,ll b){
    ll ans=1;
    while(b){
        if(b&1) ans=ans*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return ans;
}

ll inv(ll a,ll p){
     return fast_pow(a,p-2);
}

ll f(ll n,ll m){
    if (n==0&&m==0) return 0;
    if (n==0&&m==1) return 1;
    if (n>0&&m==0) return (1+(n-1)*n/2+2*(n-1)+1) % MOD;
    if (n>0&&m==1) return (n*(n+1)/2+2*n+1) % MOD;
    ll ret=((n+m+m*f(n,m-1)+n*f(n-1+m,1))%MOD)*inv(n+m,MOD) % MOD;
    return ret;
}
int main(){
    cin>>n>>m;
    n=n%MOD;
    cout<<f(n,m)<<endl;
}