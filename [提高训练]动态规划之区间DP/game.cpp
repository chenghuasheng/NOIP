//#1006. 「一本通 5.1 练习 3」矩阵取数游戏 
#include <fstream>
using namespace std;
ifstream fin("game.in");
ofstream fout("game.out");

const int MAXN=80;
const int MAXL=50;
struct HPNUM{
    short digit[MAXL]={0};
    int len=0;
    void setValue(long num){
        len=0;
        while(num>0){
            int r=num % 10;
            digit[len]=r;
            len++;
            num=num/10;
        }
    }
    HPNUM operator *(short d)const{
        HPNUM ret;
        for(int i=0;i<len;i++){
            ret.digit[i]+=digit[i]*d;
            if (ret.digit[i]>=10){
                ret.digit[i+1]+=ret.digit[i]/10;
                ret.digit[i]=ret.digit[i]%10;
            }
        }
        ret.len=len+1;
        while(ret.digit[ret.len-1]==0&&ret.len>1) ret.len--;
        return ret;
    }
    HPNUM operator +(const HPNUM other)const{
        HPNUM ret;
        ret.len=max(len,other.len);
        for(int i=0;i<ret.len;i++){
            ret.digit[i]+=digit[i]+other.digit[i];
            if (ret.digit[i]>=10){
                ret.digit[i+1]+=ret.digit[i]/10;
                ret.digit[i]=ret.digit[i]%10;
            }
        }
        if (ret.digit[ret.len]>0) ret.len++;
        return ret;
    }
    bool operator <(const HPNUM other)const{
        if (len<other.len) return true;
        else if (len>other.len) return false;
        else {
            for(int i=len-1;i>=0;i--){
                if (digit[i]<other.digit[i]) return true;
                else if (digit[i]>other.digit[i]) return false;
            }
            return false;
        }
    }
    void output(){
        for(int i=len-1;i>=0;i--) fout<<digit[i];
    }
};
HPNUM a[MAXN][MAXN];
HPNUM dp_max[MAXN][MAXN][MAXN];

int n,m;
int main(){
    fin>>n>>m;
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) {
            int c;
            fin>>c;
            a[i][j].setValue(c);
        }
    
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++) dp_max[i][j][j]=a[i][j]*2;
       
    for(int l=2;l<=m;l++){
        for(int i=0;i<n;i++)
            for(int j=0;j<m-l+1;j++){
                int k=j+l-1;
                dp_max[i][j][k]=max(a[i][j]+dp_max[i][j+1][k],a[i][k]+dp_max[i][j][k-1])*2;
            }
    }
    HPNUM ans;
    ans.setValue(0);
    for(int i=0;i<n;i++) ans=ans+dp_max[i][0][m-1];
    ans.output();
}