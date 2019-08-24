//#1028. 「一本通 5.4 练习 3」动物园
#include <fstream>
#include <iostream>
using namespace std;
ifstream fin("zoo.in");
ofstream fout("zoo.out");

const int MAXN=10000;
const int MAXC=50000;
const int INF=0x7fffffff;

int dp[MAXN+1][32];
int num[MAXN+1][32];
int e,f,l;
int fflag,lflag;
int n,c;

int main(){
    fin>>n>>c;
    for(int i=1;i<=c;i++){
        fin>>e>>f>>l;
        fflag=0;lflag=0;
        for(int j=0;j<f;j++){
            int x;
            fin>>x;
            x=(x+n-e)%n;
            fflag+=1<<x;
        }
        for(int j=0;j<l;j++){
            int y;
            fin>>y;
            y=(y+n-e)%n;
            lflag+=1<<y;
        }
        for(int s=0;s<=31;s++){
           if ((s&lflag)||(~s&fflag)){
               num[e][s]++;
           } 
        }
    }
    int ans=0;
    for(int i=0;i<=31;i++){
        for(int i=0;i<=31;i++) dp[0][i]=-INF;
        dp[0][i]=0;
        for(int j=1;j<=n;j++)
            for(int s=0;s<=31;s++)
                dp[j][s]=max(dp[j-1][(s&15)<<1],dp[j-1][(s&15)<<1|1])+num[j][s];
        ans=max(ans,dp[n][i]);    
    }
    fout<<ans;
}
