#include <fstream>
using namespace std;
ifstream fin("matches.in");
ofstream fout("matches.out");

int n;
int huocai[2223]={6,2,5,5,4,5,6,3,7,6,0};
int get_huocai(int x){
    if (huocai[x]>0) return huocai[x];
    else {
        int r=x % 10;
        int q=x / 10;
        int ret=huocai[r]+get_huocai(q);
        huocai[x]=ret;
        return ret;
    }
}
int main(){
    fin>>n;
    int k=0;
    n-=4;
    for(int a=0;a<=1111;a++){
        for(int b=a;b<=1111;b++){
            int c=a+b;
            int total=get_huocai(a)+get_huocai(b)+get_huocai(c);
            if (total==n){
                if (a==b) k++;
                else k+=2;
            }
        }
    }
    fout<<k;
}