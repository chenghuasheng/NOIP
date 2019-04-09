#include <fstream>
#include <string>
using namespace std;
ifstream fin("delete.in");
ofstream fout("delete.out");

string num;
int s;
int main(){
    fin>>num;
    fin>>s;
    int l=num.length();
    if (s>=l) fout<<0;
    else {
        int i=0;
        for(int k=0;k<s;k++){
            if (num[i]<num[i+1]) num[i+1]=num[i];
            i++;
        }
        for(int j=i;i<l;i++) fout<<num[i];
    } 
}