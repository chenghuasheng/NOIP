//#1019. 「一本通 5.3 例 3」Windy 数
#include <fstream>
#include <iostream>

using namespace std;
ifstream fin("windy.in");
ofstream fout("windy.out");

const int MAXLEVEL=31;
int f[MAXLEVEL+1][11];//f[i][j] 表示高度为i的完全10叉树中当根结点为j时，
                    //由根结点到叶结点的路径所组成的数是windy数的个数，
                    //其中当j=10时表示先导为0的情形
                    //而当j=0时，0不作为先导0，要与后面的数位作比较
int a,b;
void dp(){
    for(int i=0;i<=9;i++) f[0][i]=1;
    f[0][10]=1;
    for(int i=1;i<=MAXLEVEL;i++){
        for(int j=0;j<=9;j++)
            for(int k=0;k<=9;k++){
                if (abs(j-k)>=2) f[i][j]+=f[i-1][k];
            }
            for(int k=1;k<=10;k++) f[i][10]+=f[i-1][k];
    }
}
int calc(int x){
    int t[MAXLEVEL+1]={0};
    int k=0;
    while(x>0){
        int d=x % 10;
        t[k]=d;
        k++;
        x= x / 10;
    }
    int tot=-2,ans=0;
    int i=max(k-1,0);
    for(;i>=0;i--){
        int d=t[i];
        if (d>0){
            if (tot==-2) ans+=f[i][10];//当计算最高位的时候，要加上先导为0的情形
            else if (abs(0-tot)>=2) ans+=f[i][0];//非最高位的时候要看0与前一位是否满足要求
        }
        for(int j=1;j<d;j++) {
            if (abs(j-tot)>=2) ans+=f[i][j];
        }
        
        if (abs(d-tot)<2) break;
        if (i==0) ans++;
        tot=d;
    }
    return ans;
}
int main(){
    fin>>a>>b;
    dp();
    int n1=calc(a-1);
    int n2=calc(b);
    fout<<n2-n1;
}