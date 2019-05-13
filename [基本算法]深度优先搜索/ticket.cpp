#include <fstream>
#include <algorithm>
#include<iostream>
using namespace std;
ifstream fin("ticket.in");
ofstream fout("ticket.out");
char yy[5]={'a','e','i','o','u'};
bool isyy[256];
char letter[26];
int L,C;
char ans[15];
int num;
void dfs(int dep,int k){
    if (dep>=L){
        int yycount=0;
        for(int i=0;i<dep;i++) if (isyy[int(ans[i])]) yycount++;
        if (yycount>0&&yycount<=L-2) {
            num++;
            if (num<=25000) {
                for(int i=0;i<dep;i++) fout<<ans[i];
                fout<<endl;
            }
            
        }
    }else {
        for(int i=k;i<C;i++){
            ans[dep]=letter[i];
            dfs(dep+1,i+1);
        }
    }
}
int main(){
    fin>>L>>C;
    for(int i=0;i<C;i++) fin>>letter[i];
    for(int i=0;i<5;i++) isyy[int(yy[i])]=true;
    sort(letter,letter+C);
    dfs(0,0);
    system("pause");
}