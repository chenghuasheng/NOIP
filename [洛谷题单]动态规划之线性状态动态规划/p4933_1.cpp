#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN=1000;
const int MAXV=20000;
int n;
int high[MAXV+1];
int solutions[MAXN][MAXV*2];
vector<int> gc[MAXN];

int main(){
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>high[i];
    }
    for(int i=1;i<n;i++){
        for(int k=0;k<i;k++){
            for(int p=0;p<gc[k].size();p++){
                int curGc=gc[k][p];
                if (high[k]+curGc==high[i]){
                    int newSolutions=solutions[k][curGc];
                    if (solutions[i][curGc]==0) gc[i].push_back(curGc);
                    solutions[i][curGc]=(solutions[i][curGc]+newSolutions) % 998244353;
                }
            }
            int curGc=high[i]-high[k];
            if (solutions[i][curGc]==0) gc[i].push_back(curGc);
            solutions[i][curGc]=(solutions[i][curGc]+1) % 998244353;
        }
    }
    int ans=n;
    for(int i=0;i<n;i++){
        for(int p=0;p<gc[i].size();p++) ans=(ans + solutions[i][gc[i][p]]) % 998244353;
    }
    cout<<ans<<endl;
}