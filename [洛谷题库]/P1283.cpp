#include <iostream>
#include <vector>
using namespace std;
const int MAXN=16;
struct Rec{
    int x1,y1,x2,y2;
    int color;
};
Rec recs[MAXN+1];
vector<int> G[MAXN+1];
int n;
int minTimes[1<<MAXN][MAXN+1];
inline bool contains(int s, int i){
    return ((s>>(i-1))&1)==1;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        int x1,y1,x2,y2,color;
        cin>>y1>>x1>>y2>>x2>>color;
        recs[i]={x1,y1,x2,y2,color};
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++){
            if (i!=j&&recs[i].y1==recs[j].y2&&recs[i].x2>recs[j].x1){
                G[i].push_back(j);
            }
        }
    int maxState=(1<<n)-1;
    for(int s=1;s<=maxState;s++)
        for(int i=1;i<=n;i++) minTimes[s][i]=n+1;
    
    for(int i=1;i<=n;i++) 
      if (recs[i].y1==0) minTimes[1<<(i-1)][i]=1;
    
    for(int s=1;s<=maxState;s++)
        for(int i=1;i<=n;i++){
            if (!contains(s,i)) continue;
            int prevState=(s-(1<<(i-1)));
            if (prevState<=0) continue;
            bool can=true;
            for(int k=0;k<G[i].size();k++){
                int j=G[i][k];
                if (!contains(prevState,j)) {
                    can=false;
                    break;
                }
            }
            if (can){
                for(int i1=1;i1<=n;i1++) 
                    if (recs[i].color==recs[i1].color) minTimes[s][i]=min(minTimes[s][i],minTimes[prevState][i1]);
                    else minTimes[s][i]=min(minTimes[s][i],minTimes[prevState][i1]+1);
            }
        }
    
    int ans=n+1;
    for(int i=1;i<=n;i++) {
        //cout<<minTimes[maxState][i];
        ans=min(ans,minTimes[maxState][i]);
    }
    cout<<ans;
}