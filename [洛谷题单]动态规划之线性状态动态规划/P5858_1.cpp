#include <iostream>
#include <climits>
#include <cstdio>

using namespace std;
const int MAXN=5500;
const int MAXW=5500;
int n,w,s;
long long a[MAXN+1];
long long totalNJD[MAXN+1][MAXW+1];
long long val[MAXW+1];
int pos[MAXW+1];

int main(){
    scanf("%d %d %d",&n,&w,&s);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=w;j++) {
            totalNJD[i][j]=LONG_LONG_MIN;
        }
    totalNJD[1][1]=1*a[1];
    for(int i=2;i<=n;i++){
        int left=1,right=1;
        int last=min(i-1,w);
        val[left]=totalNJD[i-1][last];
        pos[left]=last;
        for(int j=min(i,w);j;j--){
            while(pos[left]>j+s-1&&left<=right) left++;
            if (j>1){
                while(val[right]<totalNJD[i-1][j-1]&&left<=right) right--;
                pos[++right]=j-1;
                val[right]=totalNJD[i-1][j-1];
            }
            if (left<=right){
                totalNJD[i][j]=val[left]+j*a[i];
            }
        }   
    }
    long long ans=LONG_LONG_MIN;
    for(int j=1;j<=w;j++) ans=max(ans,totalNJD[n][j]);
    printf("%lld",ans);
}
