//#1004. 「一本通 5.1 练习 1」括号配对 
#include <fstream>
using namespace std;
ifstream fin("kh.in");
ofstream fout("kh.out");
const int MAXN=100;
string s;
int dp_min[MAXN][MAXN];

int main(){
    fin>>s;
    int len=s.length();
    for(int i=0;i<len;i++) dp_min[i][i]=1;
    for(int i=0;i<len-1;i++) {
        if ((s[i]=='['&&s[i+1]==']')||(s[i]=='('&&s[i+1]==')')) dp_min[i][i+1]=0;
        else dp_min[i][i+1]=2;
    }
    for (int l=3;l<=len;l++){
        for(int i=0;i<len-l+1;i++){
            int j=i+l-1;
            dp_min[i][j]=0x7fffffff;
            if ((s[i]=='['&&s[j]==']')||(s[i]=='('&&s[j]==')')) dp_min[i][j]=dp_min[i+1][j-1];
            for (int k=i;k<j;k++){
                dp_min[i][j]=min(dp_min[i][j],dp_min[i][k]+dp_min[k+1][j]);
            }

        }
    }
    fout<<dp_min[0][len-1];
}