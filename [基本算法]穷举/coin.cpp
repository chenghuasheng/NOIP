#include <cstdio>
#include <cmath>
using  namespace std;
FILE *fpin,*fpout;

long long n;

int main(){
	fpin=fopen("coin.in","r");
	fpout=fopen("coin.out","w");
	
    fscanf(fpin,"%lld",&n);
    while(n>0){
        long long  k=(-1+sqrt(1+8.0*n))/2;
        long long n_=(k+1)*k/2;
        long long ans=k*(k+1)*(2*k+1)/6;
        ans+=(k+1)*(n-n_);
        fprintf(fpout,"%lld\n",ans);
        fscanf(fpin,"%lld",&n);
    }
}