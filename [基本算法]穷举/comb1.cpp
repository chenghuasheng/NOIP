#include <cstdio>
using namespace std;
FILE *fpin,*fpout;

const int MAXN=20;
int n,r;
int combs[MAXN];

void dfs(int x,int k){
    combs[k-1]=x;
    if (k==r){
        for(int i=0;i<k;i++) fprintf(fpout,"%d ",combs[i]);
        fprintf(fpout,"\n");
        return;
    }
    for(int x_=x+1;x_<=n;x_++) dfs(x_,k+1);
}

int main(){
	fpin=fopen("comb.in","r");
	fpout=fopen("comb.out","w");
	
    fscanf(fpin,"%d %d",&n,&r);
    for(int i=1;i<=n-r+1;i++) dfs(i,1);
}