#include <iostream>
#include <cstdio>

using namespace std;
const int MOD=1000000007;
long long ops;

long long a,b,h;
int t;
long long pow(long long x,int q){
    long long ret=1;
    while(q>0){
        if (q&1) ret=(ret*x)%MOD;
        x=(x*x)%MOD;
        q=q>>1;
    }
    return ret;
}
long long inv(long long x,int q){
    return pow(x,q-2);
}
int main(){
    scanf("%d",&t);
    for(int k=0;k<t;k++){
        scanf("%d %d %d",&a,&b,&h);
        if (a>b){
            if (b!=1) ops=((pow(b,h)*a)%MOD+((((a-b)*(pow(b,h)-1))%MOD)*inv(b-1,MOD))%MOD)%MOD;
            else ops=((pow(b,h)*a)%MOD+((a-b)*h)%MOD)%MOD;
        }else {
            ops=(pow(b,h)*a)%MOD;
        }
        printf("%lld\n",ops);
    }
}