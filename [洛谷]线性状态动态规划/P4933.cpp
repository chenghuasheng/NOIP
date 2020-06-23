#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
const int MAXN=1000;
const int MAXV=20000;
int n;
int high[MAXV+1];
int gcIndex[MAXN][MAXV*2];
vector<int> solutions[MAXN];
vector<int> gc[MAXN];

int main(){
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>high[i];
    }
    memset(gcIndex,-1,sizeof(gcIndex));
    for(int i=1;i<n;i++){
        for(int k=0;k<i;k++){
            for(int p=0;p<gc[k].size();p++){
                int curGc=gc[k][p];
                if (high[k]+curGc==high[i]){
                    int newSolutions=solutions[k][gcIndex[k][curGc]];
                    if (gcIndex[i][curGc]>=0) solutions[i][gcIndex[i][curGc]]=(solutions[i][gcIndex[i][curGc]]+newSolutions)% 998244353;
                    else {
                        gcIndex[i][curGc]=gc[i].size();
                        gc[i].push_back(curGc);
                        solutions[i].push_back(newSolutions);
                    }
                }
            }
            int curGc=high[i]-high[k];
            if (gcIndex[i][curGc]>=0) solutions[i][gcIndex[i][curGc]]=(solutions[i][gcIndex[i][curGc]]+1)% 998244353;
            else {
                gcIndex[i][curGc]=gc[i].size();
                gc[i].push_back(curGc);
                solutions[i].push_back(1);
            }
        }
    }
    int ans=n;
    for(int i=0;i<n;i++){
        for(int p=0;p<solutions[i].size();p++) ans=(ans + solutions[i][p]) % 998244353;
    }
    cout<<ans<<endl;
}