#include <cstdio>
using namespace std;
FILE *fpin,*fpout;

const int MAXN=20;
int n,r;
int combs[MAXN];

int main(){
	fpin=fopen("comb.in","r");
	fpout=fopen("comb.out","w");
	
    fscanf(fpin,"%d %d",&n,&r);
    int pos=0;
    combs[pos]=1;
    while(combs[0]<=n-r+1){
        while(pos<r-1&&combs[pos]<n) {
            pos++;
            combs[pos]=combs[pos-1]+1;
        }
        if (pos==r-1){
            for(int i=0;i<r;i++) fprintf(fpout,"%d ",combs[i]);
        	fprintf(fpout,"\n");
        }
        combs[pos]++;
        while(combs[pos]>n&&pos>0){
            pos--;
            combs[pos]++;
        }
    }
}