//#1040. 「一本通 5.5 练习 4」股票交易
#include <fstream>
#include <vector>
using namespace std;
ifstream fin("trade.in");
ofstream fout("trade.out");

const int MAXT=2000;
const int MAXP=2000;
const int INF=0x80000000;
struct daily
{
    int ap,bp,as,bs;
};
daily dailies[MAXT];
int t,p,w;
int dp_max[MAXT][MAXP+1];
vector<int> maxProfit[MAXP+1];

int main(){
    fin>>t>>p>>w;
    if (w==0) w++;

    for(int i=0;i<t;i++) {
        fin>>dailies[i].ap>>dailies[i].bp>>dailies[i].as>>dailies[i].bs;
    }
    for(int i=0;i<t;i++)
        for(int j=0;j<=p;j++) dp_max[i][j]=-INF;

    for(int i=0;i<=p;i++){
        if (i>dailies[0].as) maxProfit[i].push_back(-INF);
        else {
            dp_max[0][i]=-1*dailies[0].ap*i;
            maxProfit[i].push_back(dp_max[0][i]);
        }
    }
    for(int i=1;i<t;i++){
        for(int k=-dailies[i].bs;k<=dailies[i].as;k++){
            if (k==0){//不买也不卖
                for(int j=0;j<=p;j++) dp_max[i][j]=dp_max[i-1][j];
            }else{//有交易
                int last=i-w;
                if (last<0) {
                    if (k>0){//只能买入
                        dp_max[i][k]=max(dp_max[i][k],-k*dailies[i].ap);
                    }
                }else {
                    if (k>0){//处理买
                        for(int j=0;j<=p;j++){
                            if (maxProfit[j][last]==-INF) continue;
                            int newj=j+k;
                            if (newj>p) break;
                            dp_max[i][newj]=max(dp_max[i][newj],maxProfit[j][last]-k*dailies[i].ap);
                        }
                    }else {//处理卖
                        for(int j=-1*k;j<=p;j++){
                            if (maxProfit[j][last]==-INF) continue;
                            int newj=j-k;
                            dp_max[i][newj]=max(dp_max[i][newj],maxProfit[j][last]-k*dailies[i].bp);
                        }
                    }
                }
            }
        }
        for(int j=0;j<=p;j++){
            int t=max(maxProfit[j][i-1],dp_max[i][j]);
            maxProfit[j].push_back(t);
        }
    }
    fout<<dp_max[t-1][0];
}
