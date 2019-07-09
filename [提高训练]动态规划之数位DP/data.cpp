//#1017. 「一本通 5.3 例 1」Amount of Degrees
#include <fstream>
using namespace std;
ifstream fin("data.in");
ofstream fout("data.out");

const int MAXLEVEL=31;

int f[MAXLEVEL+1][MAXLEVEL+1];//f[i][j]表示高度为i的完全二叉树中当根结点为0时，
                                //从根结点到叶结点的路径中含有1的个数为j的叶结点数量
int x,y,k,b;
//
void dp(){
    f[0][0]=1;
    for(int i=1;i<=MAXLEVEL;i++){
        f[i][0]=f[i-1][0];
        for(int j=1;j<=i;j++) f[i][j]=f[i-1][j]+f[i-1][j-1];
    }
}
//计算小于等x内的正整数内，正好等于K个互不相同的2的幂之和的数的个数
int calc(int x,int k){
    int tot=0,ans=0;
    for(int i=31;i>=0;i--)
    {
        if (x&(1<<i)){
            ans+=f[i][k-tot];
            tot++;
            x=x^(1<<i);
            if (tot>k) break;
        }
    }
    if (tot==k&&x==0) ans++;
    return ans;
}
//将非2进制数，转换成二进制去处理。对于b进制数从高位检查，当此位数大于1时，则后面的全改为1
int trans(int x,int b){
    int t[32]={0};
    int k=0;
    while(x>0){
        int d=x % b;
        t[k]=d;
        k++;
        x= x / b;
    } 
    int over1=false;
    int ret=0;
    for(int i=k-1;i>=0;i--){
        if (t[i]>1) over1=true;
        if (over1) t[i]=1;
       ret=(ret<<1)+t[i];
    }
    return ret;
}
int main(){
    fin>>x>>y;
    fin>>k>>b;
    x=x-1;
    if (b>2){
        x=trans(x,b);
        y=trans(y,b);
    }
    dp();
    int n1=calc(x,k);
    int n2=calc(y,k);
    fout<<n2-n1;
}