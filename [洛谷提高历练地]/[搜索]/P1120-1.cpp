#include <iostream>
using namespace std;

const int MAXN=65;
int num[MAXN*50+1];
int n;
int maxv,minv;
int sum;
int ans;
void dfs(int wait,int alreadylen,int needlen,int prelen){
    if (wait==0){//已经拼完所需要的木棍数
        cout<<ans;
        exit(0);
    }else {
        if (alreadylen==needlen){//当前这一根已经拼成所需要的长度
           dfs(wait-1,0,needlen,maxv);    
        }else{
            for(int k=prelen;k>=minv;k--){//从前一小段的长度到最小长度枚举
                if (num[k]==0||alreadylen+k>needlen) continue;
                num[k]--;
                dfs(wait,alreadylen+k,needlen,k);
                num[k]++;
                if (alreadylen==0||alreadylen+k==needlen) break;//拼接一根的第一段和最后一段不需要继续枚举其他值
            } 
        }
    }
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        int k;
        cin>>k;
        if (k<=50){
            sum+=k;
            num[k]++;//每个长度的段数
            minv=min(minv,k);
            maxv=max(maxv,k);
        }
    }
    ans=maxv;
    while(ans<=sum/2){
        if (sum%ans==0){
           int k=sum / ans;
           dfs(k,0,ans,maxv);  
        }
        ans++;
    }
    cout<<sum; 

}