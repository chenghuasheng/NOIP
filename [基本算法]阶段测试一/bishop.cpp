#include <fstream>
using namespace std;

ifstream fin("bishop.in");
ofstream fout("bishop.out");

const int MAXN=20;
int n,m,maxk;
bool flag[MAXN][MAXN];

void MarkBackslash(int x,int y,bool val){
    int b=y-x;
    for(int x_=0;x_<n;x_++){
        int y_=x_+b;
        if (y_>=0&&y_<m) flag[x_][y_]=val;
    }
}

void SearchSlash(int b,int k){
    if (b>n+m-2) return;
    for(int x=0;x<n;x++){
        int y=b-x;
        if (y>=0&&y<m){
            if (!flag[x][y]){
                k++;
                if (k>maxk) maxk=k;
                MarkBackslash(x,y,true);
                SearchSlash(b+1,k);
                MarkBackslash(x,y,false);
                k--;
            }
        }
    }  
}
int main(){
    fin>>n>>m;
    SearchSlash(0,0);
    fout<<maxk; 
}