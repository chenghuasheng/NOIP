//#1040. 「一本通 5.5 练习 4」股票交易
#include <fstream>
using namespace std;
ifstream fin("trade.in");
ofstream fout("trade.out");

const int MAXT=2000;
const int MAXP=2000;
const int INF=0x7fffffff;
int ap[MAXT],bp[MAXT],as[MAXT],bs[MAXT];
int t,p,w;
int dp_max[MAXT][MAXP+1];
int maxProfit[MAXP+1][MAXT];

int main(){
    fin>>t>>p>>w;
    if (w==0) w++;
    for(int i=0;i<t;i++) {
        fin>>ap[i]>>bp[i]>>as[i]>>bs[i];
    }
    //初始化
    for(int i=0;i<t;i++)
        for(int j=0;j<=p;j++) dp_max[i][j]=-INF;
    //处理第0天
    for(int j=0;j<=p;j++){
        if (j<=as[0]) {
            dp_max[0][j]=0-ap[0]*j;
        }
        maxProfit[j][0]=dp_max[0][j];
    }
    //动规计算第1至第t-1天 
    for(int i=1;i<t;i++){
        //处理当天没有交易的情形
        for(int j=0;j<=p;j++) dp_max[i][j]=dp_max[i-1][j];
        //处理当天有交易的情形
        int last=i-w;//上一次交易的最晚日期
        if (last<0){//即上一次交易不存在，只能买入且是初始买入
            for(int j=1;j<=as[i];j++){
                if (j>p) break;
                dp_max[i][j]=max(dp_max[i][j],0-ap[i]*j);
            }
        }else {
            //处理买
            for(int j=1;j<=as[i];j++){
                for(int j1=0;j1<=p;j1++){
                    if (maxProfit[j1][last]==-INF) break;
                    int newj=j1+j;
                    if (newj>p) break;
                    dp_max[i][newj]=max(dp_max[i][newj],maxProfit[j1][last]-ap[i]*j);
                }
            }
            //处理卖
            for(int j=1;j<=bs[i];j++){
                for(int j1=j;j1<=p;j1++){
                    if (maxProfit[j1][last]==-INF) break;
                    int newj=j1-j;
                    dp_max[i][newj]=max(dp_max[i][newj],maxProfit[j1][last]+bp[i]*j);
                }
            }
        }
        //更新前i天持有j股的最大收益
        for(int j=0;j<=p;j++){
            maxProfit[j][i]=max(maxProfit[j][i-1],dp_max[i][j]);
        }
    }
    fout<<dp_max[t-1][0];
}
