#include <fstream>
using namespace std;
ifstream fin("match.in");
ofstream fout("match.out");

const int MAXN=1000;
int huocai[MAXN];
int n;
int mi2[17];

int main(){
    mi2[0]=1;
    for(int i=1;i<17;i++) mi2[i]=mi2[i-1]*2;
    fin>>n;
    for(int i=0;i<n;i++) fin>>huocai[i];
    int ret=huocai[0];
    for(int i=1;i<n;i++) ret=ret^huocai[i];
    if (ret==0) fout<<"lose";
    else {
        int k=16;
        while((mi2[k]&ret)==0 && k>0) k--;
        for(int i=0;i<n;i++){
            int inc=0;
            if ((huocai[i]&mi2[k])>0){
                inc-=mi2[k];
                k--;
                while(k>=0){
                    if ((mi2[k]&ret)>0){
                        inc+=(mi2[k]&ret)-2*(mi2[k]&huocai[i]);
                    }
                    k--;
                }
                huocai[i]+=inc;
                fout<<-1*inc<<' '<<i+1<<endl;
                break;
            }
        }
        for(int i=0;i<n;i++)
            fout<<huocai[i]<<' ';
    }
}