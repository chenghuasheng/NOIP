#include <iostream>
using namespace std;
const int MAXN=100000;
int n;
int high[MAXN];
int dp[MAXN];//dp[i] 表示前 i 枚导弹，在第 i 枚被拦截的前提下，能拦截的最大导弹数
int ans1,ans2;
int minHigh[MAXN];//minHigh[k] 记录第 k 套系统拦截导弹的最低高度

int main(){
    int i=0;
    int a;
    while(cin>>a){
        high[i]=a;
        i++;
    }
    n=i;
    //动规计算出 dp[i]
    for(int i=0;i<n;i++) dp[i]=1;
    for(int i=1;i<n;i++){
        for(int k=0;k<i;k++) 
            if (high[k]>=high[i]) dp[i]=max(dp[i],dp[k]+1);
    }
    //找出最大的 dp[i]
    for(int i=0;i<n;i++) 
        if (dp[i]>ans1) ans1=dp[i];

    //计算需要多少套拦截系统
    int ans2=1;
    minHigh[0]=high[0];

    for(int i=1;i<n;i++){
        if (minHigh[ans2-1]<high[i]){
            ans2++;
            minHigh[ans2-1]=high[i];
        }else {
            int k=lower_bound(minHigh,minHigh+ans2,high[i])-minHigh;
            minHigh[k]=high[i];
        }
    }
    //输出
    cout<<ans1<<endl;
    cout<<ans2;
}