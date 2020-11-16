#include <iostream>
#define ll long long
const ll MOD=998244353;
const ll MAXM=1000000;
using namespace std;
ll n,m;
ll f[MAXM+1];

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
int main(){
    cin>>n>>m;
    n=n%MOD;
    f[0]=(1+(n-1)*n/2+2*(n-1)+1)%MOD;
    f[1]=(n*(n+1)/2+2*n+1)%MOD;
    if (m>=2){
        for(int i=2;i<=m;i++){
            f[i]=((n+i+n*(((n+i-1)*(n+i)/2+2*(n+i-1)+1)%MOD)+i*f[i-1])%MOD)*inv(n+i,MOD)%MOD;
        }
    }
    cout<<f[m]<<endl;
}
