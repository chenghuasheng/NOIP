//#1026. 「一本通 5.4 练习 1」涂抹果酱
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;
ifstream fin("paint.in");
ofstream fout("paint.out");
const int MAXN=10000;
const int MAXS=2000;
int dp[MAXN+1][MAXS];
vector<int> states;
int n,m;

bool check(int s){
    int pre=-1;
    for(int i=0;i<m;i++){
        int cur=s%3;
        if (pre==cur) return false;
        pre=cur;
        s=s/3;
    }
    return true;
}
bool check1(int s1,int s2){
    for(int i=0;i<m;i++){
        int cur1=s1%3;
        int cur2=s2%3;
        if (cur1==cur2) return false;
        s1=s1/3;
        s2=s2/3;
    }
    return true;
}

int k;
int flagk;
int mi3[20];

int main(){
    fin>>n>>m;
    fin>>k;
    for(int i=0;i<m;i++){
        int a;
        fin>>a;
        flagk=flagk*3+(a-1);
    }
    mi3[0]=1;
    for(int i=1;i<20;i++) mi3[i]=3*mi3[i-1];
    for(int s=0;s<=mi3[m]-1;s++){
        if (check(s)) states.push_back(s);
    }
    int count=states.size();
    for(int i=0;i<count;i++){
        int s=states[i];
        if ((k==1)&&(s!=flagk)) continue;
        dp[1][s]=1;
    }
    
    for(int i=2;i<=n;i++){
        for(int i1=0;i1<count;i1++){
            int s1=states[i1];
            if ((i==k)&&(s1!=flagk)) continue;
            for(int i2=0;i2<count;i2++){
                int s2=states[i2];
                if (check1(s1,s2)){
                    dp[i][s1]=(dp[i][s1]+dp[i-1][s2])%1000000;
                }
            } 
        }
    }
    int ans=0;
    for(int i=0;i<count;i++){
        int s=states[i];
        ans=(ans+dp[n][s]) % 1000000;
    }
    fout<<ans;
}