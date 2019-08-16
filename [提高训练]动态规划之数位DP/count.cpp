//#1023. 「一本通 5.3 练习 4」数字计数
#include <fstream>
#include <iostream>

using namespace std;
ifstream fin("count.in");
ofstream fout("count.out");

const int MAXL=12;
long long f[MAXL+1][11][10];//f[i][j][d]表示在第i层以j为根的子树中的所有数含数字d的个数
            //j=10时表示0为前置0
long long mi10[MAXL];
long long a,b;
long long ans1[10],ans2[10];
void dp(){
    for(int i=0;i<=9;i++) f[0][i][i]=1;
    f[0][10][0]=1;
    for(int i=1;i<=MAXL;i++){
        for(int j=0;j<=9;j++){//当前i层数字为j
            f[i][j][j]+=mi10[i];
            for(int d=0;d<=9;d++){//统计d
                for(int k=0;k<=9;k++){//下一层数字为k
                    f[i][j][d]+=f[i-1][k][d];
                }
            }
        }
        //统计j=10,即前置0的情况
        for(int d=0;d<=9;d++){//统计d有多少个
            for(int k=1;k<=10;k++){//下一层数字为k
                f[i][10][d]+=f[i-1][k][d];
            }
        }
    }
}
void calc(long long x,long long ans[]){
    int t[MAXL+1]={0};
    int k=0;
    while(x>0){
        int d=x % 10;
        t[k]=d;
        k++;
        x= x / 10;
    }
    int tot=-1;
    for(int k=0;k<=9;k++) ans[k]=0;
    int w=max(k-1,0);
    for(int i=w;i>=0;i--){
        int d=t[i];
        if (tot<0){//最高位时，应该加上的是前置0的情形
                //然后加1到d-1的情形
            if (d>0) {
                for(int k=0;k<=9;k++) ans[k]+=f[i][10][k];
            }
            for(int j=1;j<d;j++) {
                for(int k=0;k<=9;k++) ans[k]+=f[i][j][k];
            }
        }else{ //非最高位直接加0到d-1的情形
            for(int j=0;j<d;j++) {
                for(int k=0;k<=9;k++) ans[k]+=f[i][j][k];
                for(int k=w;k>i;k--) {
                    ans[t[k]]+=mi10[i];
                }
            }
        }
        ans[d]++;
        tot=d;
    }
}
int main(){
    mi10[0]=1;
    for(int i=1;i<=MAXL;i++) mi10[i]=10*mi10[i-1];
    dp();
    fin>>a>>b;
    a=a-1;
    calc(a,ans1);
    calc(b,ans2);
    for(int k=0;k<=9;k++) fout<<ans2[k]-ans1[k]<<' ';
}