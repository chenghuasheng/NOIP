#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("max.in");
ofstream fout("max.out");

const int MAXN=20;
string num[MAXN];
int n;

bool cmp(string num1,string num2){
    int l1=num1.length();
    int l2=num2.length();
    int i1=0,i2=0;
    while(1){
        if (num1[i1]==num2[i2]){
            i1++;
            i2++;
            if (i1==l1&&i2==l2) return false;
            else {
                i1=i1%l1;
                i2=i2%l2;
            }
        }
        else  return (num1[i1]>num2[i2]);
    }
}
int main(){
    fin>>n;
    for(int i=0;i<n;i++) fin>>num[i];
    sort(num,num+n,cmp);
    for(int i=0;i<n;i++) fout<<num[i];
}