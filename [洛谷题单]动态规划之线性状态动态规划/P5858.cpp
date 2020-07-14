#include <iostream>
#include <climits>
#include <cstdio>
using namespace std;
const int MAXN=5500;
const int MAXW=5500;
int n,w,s;
long long a[MAXN+1];
long long totalNJD[MAXN+1][MAXW+1];
int main(){
    scanf("%d %d %d",&n,&w,&s);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=w;j++) {
            totalNJD[i][j]=LONG_LONG_MIN;
        }
    totalNJD[1][1]=1*a[1];
    for(int i=2;i<=n;i++){
        for(int j=1;j<=min(i,w);j++){
            for(int k=max(j-1,1);k<=min(j+s-1,w);k++){
               if (totalNJD[i-1][k]==LONG_LONG_MIN) break;
               long long t=totalNJD[i-1][k]+j*a[i];
               if (t>totalNJD[i][j]) totalNJD[i][j]=t;
               else break; 
            }
        }  
    }
    long long ans=LONG_LONG_MIN;
    for(int j=1;j<=w;j++) ans=max(ans,totalNJD[n][j]);
    printf("%lld",ans);
}
