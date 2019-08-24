//#1027. 「一本通 5.4 练习 2」炮兵阵地
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
ifstream fin("cannon.in");
ofstream fout("cannon.out");
const int MAXN=100;
const int MAXM=10;
const int MAXS=1024;

int n,m;
int flag[MAXN+1];
int dp[MAXN+1][MAXS][MAXS];
vector<int> states;
int num1[MAXS];

int check_cout(int s){
    if (s&(s<<1)) return -1;
    if (s&(s<<2)) return -1;
    int k=0;
    while(s>0){
        k+=s&1;
        s=s>>1;
    }
    return k;
}
int main(){
    fin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=0;j<m;j++){
            char c;
            fin>>c;
            flag[i]=flag[i]<<1;
            if (c=='H') flag[i]+=1;
        }
    }
    for(int s=0;s<=(1<<m)-1;s++){
        int t=check_cout(s);
        if (t>=0) {
            num1[s]=t;
            //cout<<s<<' '<<num1[s]<<endl;
            states.push_back(s); 
        }
    }
    int count=states.size();
    for(int i=1;i<=n;i++){
        for(int k=0;k<count;k++){
            int s=states[k];
            if (s&flag[i]) continue;
            for(int k1=0;k1<count;k1++){
                int s1=states[k1];
                for(int k2=0;k2<count;k2++){
                    int s2=states[k2];
                    if ((s&s1)||(s&s2)||(s1&s2)) continue;
                    dp[i][s][s1]=max(dp[i][s][s1],dp[i-1][s1][s2]+num1[s]);
                }
            }
        }
    }
    int ans=0;
    for(int k1=0;k1<count;k1++){
        int s1=states[k1];
        for(int k2=0;k2<count;k2++){
            int s2=states[k2];
            ans=max(ans,dp[n][s1][s2]);
            
            //cout<<s1<<' '<<s2<<' '<<dp[2][s1][s2]<<endl;
        }
    }
    fout<<ans;

}

