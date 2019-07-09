//#1018. 「一本通 5.3 例 2」数字游戏
#include <fstream>
using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");

const int MAXLEVEL=31;
int f[MAXLEVEL+1][10];//f[i][j] 表示高度为i的完全10叉树中当根结点为j时，由根结点到叶结点的路径所组成的数是不降数的个数
int a,b;

void dp(){
    for(int i=0;i<=9;i++) f[0][i]=1;
    for(int i=1;i<=MAXLEVEL;i++)
        for(int j=0;j<=9;j++){
            for(int k=j;k<=9;k++) f[i][j]+=f[i-1][k];
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
    int tot=0,ans=0;
    int i=max(k-1,0);
    for(;i>=0;i--){
        int d=t[i];
        if (d<tot) break;
        for(int j=tot;j<d;j++) ans+=f[i][j];
        if (i==0) ans++;
        tot=d;
    }
    return ans;
}

int main(){
    dp();
    while(fin>>a) {
        fin>>b;
        int n1=calc(a-1);
        int n2=calc(b);
        fout<<n2-n1<<endl;
    }
}