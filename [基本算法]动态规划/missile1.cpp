#include <fstream>
#include<algorithm>

using namespace std;
ifstream fin("missile.in");
ofstream fout("missile.out");
const int MAXN=1000;
int n;
int high[MAXN];
int l1,l2;
int d1[MAXN],d2[MAXN];

int main(){
    fin>>n;
    for(int i=0;i<n;i++) fin>>high[i];
    l1=0;
    d1[0]=high[0];
    l2=0;
    d2[0]=high[0];

    for(int i=1;i<n;i++){
        if (high[i]<=d1[l1-1]) d1[l1++]=high[i];
        else{
            int k=upper_bound(d1,d1+l1,high[i],greater<int>())-d1;
            d1[k]=high[i];
        }
        if (high[i]>d2[l2-1]) d2[l2++]=high[i];
        else {
            int k=lower_bound(d2,d2+l2,high[i])-d2;
            d2[k]=high[i];
        }
    }
    
    //输出
    fout<<l1<<endl<<l2;
}