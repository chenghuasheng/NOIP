#include <iostream>
#include <cstring>

using namespace std;
const int MAXN=20;
const int MAXS=MAXN*100;
int a[MAXN+1];
int n,m;
bool removed[MAXN+1];
bool can[MAXS+1];
int maxtotal;
void calc(){
    memset(can,false,sizeof(can));
    can[0]=true;
    int sum=0;
    int total=0;
    for(int i=1;i<=n;i++){
        if (!removed[i]){
            sum+=a[i];
            for(int j=sum;j>=a[i];j--) //此循环要从大到小枚举，否则a[i]就会被多次使用。这是一个背包问题
                if (!can[j]&&can[j-a[i]]){
                    can[j]=true;
                    total++;
                }
        }
        /*上面这部分也可以这样写
        if (!removed[i]){
            for(int j=sum;j>=0;j--) 
                if (can[j]&&!can[j+a[i]]){
                    can[j+a[i]]=true;
                    total++;
                }   
            sum+=a[i];
        }*/
    }
    maxtotal=max(maxtotal,total);
}
void dfs(int start,int num){
    if (num==0){
        calc();
    }else {
        for(int i=start;i<=n-(num-1);i++){
            removed[i]=true;
            dfs(i+1,num-1);
            removed[i]=false;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
    }
    dfs(1,m);
    cout<<maxtotal;
    system("pause");
}