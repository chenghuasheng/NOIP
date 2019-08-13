//#1023. 「一本通 5.3 练习 4」数字计数
#include <fstream>
using namespace std;
ifstream fin("count.in");
ofstream fout("count.out");

const int MAXL=12;
int f[MAXL+1][10][10];
int mi10[MAXL];

void dp(){
    for(int i=0;i<=9;i++) f[0][i][i]=1;
    for(int i=1;i<=MAXL;i++){
        for(int j=0;j<=9;j++){
            for(int d=0;d<=9;d++){
                for(int k=0;k<=9;k++){
                    f[i][j][d]+=f[i-1][k][d];
                    if (i==d) f[i][j][d]+=mi10[i];
                }
                
            }
        }
    }
}

int main(){
    
}