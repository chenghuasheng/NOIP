//http://www.joyoi.cn/problem/NOIP2017Day1  п║©╜╣дри╩С 
#include<iostream>
#include<fstream>

using namespace std;
ifstream fin("math.in");
ofstream fout("math.out");
int a,b;
long long ans;
int main(){
	fin>>a>>b;
	ans=a*b-a-b;
	fout<<ans;
}
