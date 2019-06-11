#include <fstream>
#include <iostream>

using namespace std;
ifstream fin("lcs.in");
ofstream fout("lcs.out");
const int MAXL=5000;
string s1,s2;
int dp[MAXL+1][MAXL+1];
int l1,l2;

int main(){
    fin>>s1;
    fin>>s2;
    l1=s1.length();
    l2=s2.length();

    for(int i=1;i<=l1;i++)
        for(int j=1;j<=l2;j++){
            if (s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
        }
    fout<<dp[l1][l2];
}
