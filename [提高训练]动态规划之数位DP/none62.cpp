#include <fstream>
using namespace std;
ifstream fin("none62.in");
ofstream fout("none62.out");
const int MAXL=7;
int f[MAXL+1][10];
int a,b;

void dp(){
    for(int i=0;i<=9;i++) {
        if (i==4) f[0][i]=0;
        else f[0][i]=1;
    }
    for(int i=1;i<=MAXL;i++){
        for(int j=0;j<=9;j++){
            if (j==4) f[i][j]=0;
            else 
                for(int k=0;k<=9;k++){
                    if (!(j==6&&k==2)) f[i][j]+=f[i-1][k];
                }
        }
        
    }
}
int calc(int x){
    int t[MAXL+1]={0};
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
        for(int j=0;j<d;j++) {
            if (!(tot==6&&j==2)) ans+=f[i][j];
        }
        if (d==4) break;
        if (tot==6&&d==2) break;
        if (i==0) ans++;
        tot=d;
    }
    return ans;
}
int main(){
    dp();
    fin>>a>>b;
    while(!(a==0&&b==0)){
        int n1=calc(a-1);
        int n2=calc(b);
        fout<<n2-n1<<endl;
        fin>>a>>b;
    }
}