//此题为贪心的反例，看似可以贪心，但实际贪心有错误，应该用动态规划来做
#include <fstream>
using namespace std;
ifstream fin("pebble.in");
ofstream fout("pebble.out");

const int MAXN=100;
int stones[MAXN*2];
int totalstones[MAXN*2][MAXN];
int minscore[MAXN*2][MAXN];
int maxscore[MAXN*2][MAXN];
int lastminscore;
int lastmaxscore;

int n;
int main(){
    fin>>n;
    for(int i=0;i<n;i++) fin>>stones[i];
    int m=n*2-1;
    for(int i=n;i<m;i++) stones[i]=stones[i-n];
    for(int i=0;i<m;i++) totalstones[i][1]=stones[i];
    for(int k=2;k<=n;k++) 
        for(int i=0;i<m-k+1;i++) totalstones[i][k]=totalstones[i][k-1]+stones[i+k-1];

    
    for(int k=2;k<=n;k++){
        for(int i=0;i<m-k+1;i++){
            minscore[i][k]=minscore[i][1]+minscore[i+1][k-1]+totalstones[i][1]+totalstones[i+1][k-1];
            maxscore[i][k]=maxscore[i][1]+maxscore[i+1][k-1]+totalstones[i][1]+totalstones[i+1][k-1];
            for(int j=2;j<k;j++){
                minscore[i][k]=min(minscore[i][k],minscore[i][j]+minscore[i+j][k-j]+totalstones[i][j]+totalstones[i+j][k-j]);
                maxscore[i][k]=max(maxscore[i][k],maxscore[i][j]+maxscore[i+j][k-j]+totalstones[i][j]+totalstones[i+j][k-j]);
            }
        }
    }
    
    lastminscore=minscore[0][n];
    lastmaxscore=maxscore[0][n];
    for(int i=1;i<n;i++){
        if (minscore[i][n]<lastminscore) lastminscore=minscore[i][n];
        if (maxscore[i][n]>lastmaxscore) lastmaxscore=maxscore[i][n];
    }
    fout<<lastminscore<<endl;
    fout<<lastmaxscore<<endl;
}