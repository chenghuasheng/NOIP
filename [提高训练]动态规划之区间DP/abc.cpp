//#1003. 「一本通 5.1 例 3」凸多边形的划分
#include<fstream>
using namespace std;
ifstream fin("abc.in");
ofstream fout("abc.out");
const int MAXN=50;
const int MAXL=100;
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
    HPNUM operator *(const HPNUM other)const{
        HPNUM ret;
        for(int i=0;i<len;i++)
            for(int j=0;j<other.len;j++){
                int k=i+j;
                ret.digit[k]+=digit[i]*other.digit[j];
                if (ret.digit[k]>=10){
                    ret.digit[k+1]+=ret.digit[k] / 10;
                    ret.digit[k]=ret.digit[k] % 10;
                }
            }
        ret.len=len+other.len;
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

HPNUM w[MAXN];
HPNUM dp_min[MAXN][MAXN];//dp_min[i][j]表示区间[i,j]的顶点所组成的多边形划分成的三角形所得的顶点权值乘积和的最小值
int n;

int main(){
    fin>>n;
    for(int i=0;i<n;i++) {
        int a;
        fin>>a;
        w[i].setValue(a);
    }
    
    for(int len=3;len<=n;len++){
        for(int i=0;i<n-len+1;i++){
            int j=i+len-1;
            dp_min[i][j]=dp_min[i][i+1]+dp_min[i+1][j]+w[i]*w[i+1]*w[j];
            for(int k=i+1;k<j;k++){
                dp_min[i][j]=min(dp_min[i][j],dp_min[i][k]+dp_min[k][j]+w[i]*w[k]*w[j]);
            }
        }
    }
    dp_min[0][n-1].output();
}
            