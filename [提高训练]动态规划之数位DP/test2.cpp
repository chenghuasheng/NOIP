//#1020. 「一本通 5.3 练习 1」数字游戏
#include <fstream>
#include <cstring>

using namespace std;
ifstream fin("test.in");
ofstream fout("test.out");
const int MAXL=10;
const int MAXN=100;
int f[MAXL+1][10][MAXN];
int a,b,n;
void dp(){
    for(int i=0;i<=9;i++){
        f[0][i][i%n]=1;
    }
    for(int i=1;i<=MAXL;i++){
        for(int j=0;j<=9;j++){
            for(int k=0;k<=9;k++){
                for(int r=0;r<n;r++) 
                    f[i][j][(j+r)%n]+=f[i-1][k][r];
            }
        }
    }
}
int calc(int x){
    int t[MAXL + 1] = { 0 };
    int k = 0;
    while (x > 0) {
        int d = x % 10;
        t[k] = d;
        k++;
        x = x / 10;
    }
    int ans=0,tot=0;
    int i = max(k - 1, 0);
    for (; i >= 0; i--) {
        int d = t[i];
        for(int j=0;j<d;j++){
            for(int r=0;r<n;r++)
                if ((tot+r)%n==0) ans+=f[i][j][r];
        }
        tot+=d;
        if ((i==0)&&(tot%n==0)) ans++;
    }
    return ans;
}
int main(){
    while(fin>>a>>b>>n){
        memset(f,0,sizeof(f));
        dp();
        int n1=calc(a-1);
        int n2=calc(b);
        fout<<n2-n1<<endl;
    }
}