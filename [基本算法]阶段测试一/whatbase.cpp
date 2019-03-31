#include <fstream>
using namespace std;

ifstream fin("whatbase.in");
ofstream fout("whatbase.out");

int k,a,b;

long long ndigit(int m,int n){
    long long ret=0;
    int p=m;
    int mi=1;
    while(p>0){
        int q=p%10;
        ret+=q*mi;
        p=p/10;
        mi=mi*n;
    }
    return ret;
}

int main(){
    fin>>k;
    for(int i=0;i<k;i++){
        fin>>a>>b;
        for(int x=10;x<=15000;x++){
            long long m1=ndigit(a,x);
            int left,right;
            if (a>b){
                left=x+1;
                right=15000;
            }else {
                left=10;
                right=x;
            }
            bool find=false;
            while(left<=right){
               int y=(left+right)/2;
               long long m2=ndigit(b,y);
               if (m2==m1){
                   fout<<x<<' '<<y<<endl;
                   find=true;
                   break;
               }else if (m2>m1){
                   right=y-1;
               }else {
                   left=y+1;
               }
            }
            if (find) break;
        }
    }
}