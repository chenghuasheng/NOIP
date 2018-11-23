#include<iostream>
#include<fstream>
#include<algorithm> 
#include<cstring>
using namespace std;
ifstream fin("money.in");
ofstream fout("money.out");
int T;
int n;
int a[100];
bool flag[25001];
int main(){
	fin>>T;
	for(int i=0;i<T;i++){
		fin>>n;
		for(int j=0;j<n;j++) fin>>a[j];
		sort(a,a+n);
		memset(flag,false,sizeof(flag));
		int max=a[n-1];
		flag[0]=true;
		int m=0;
		for(int j=0;j<n;j++){
			if (flag[a[j]]) continue;
			m++;
			for(int k=a[j];k<=max;k++) flag[k]=flag[k]|flag[k-a[j]];	
		}
		cout<<m<<endl;
	}
}
