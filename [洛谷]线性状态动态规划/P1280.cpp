#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN=10000;
const int MAXK=10000;

int p[MAXK],t[MAXK];
int dp[MAXN+2];
bool calculted[MAXN+2];
vector<int> taskTree[MAXN+1];

int n,k;
void tree_dp(int i){
    if (i>n||calculted[i]) return;
    int size=taskTree[i].size();
    if (size==0){
        tree_dp(i+1);
        dp[i]=dp[i+1];
    }else {
        dp[i]=n;
        for(int j=0;j<size;j++){
            int curTask=taskTree[i][j];
            int finishTime=p[curTask]+t[curTask]-1;
            tree_dp(finishTime+1);
            dp[i]=min(dp[i],t[curTask]+dp[finishTime+1]);
        }
    }
    calculted[i]=true;
}
int main(){
    cin>>n>>k;
    for(int i=0;i<k;i++) {
        cin>>p[i]>>t[i];
        taskTree[p[i]].push_back(i);
    }
    
    fill(calculted,calculted+n+1,false);
    tree_dp(1);
    cout<<n-dp[1]; 
}

