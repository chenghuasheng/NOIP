// http://www.joyoi.cn/problem/NOIP2017-2 时间复杂度 
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;
ifstream fin("complexity.in");
ofstream fout("complexity.out");

const int ZERO=-100;
int T; 
bool flag[26];
stack<char> varStack;
stack<int> complexStack;
vector<string> progs[10];
int progSizes[10];
string progComplexs[10];

string int2str(const int &int_temp)  
{  
    string string_temp;
	stringstream ss;  
    ss<<int_temp;  
    string_temp=ss.str();   //此处也可以用 stream>>string_temp  
    return string_temp;
}  
int str2int(const string &string_temp){
	int int_temp;
	stringstream ss(string_temp); 
	ss>>int_temp;
	return int_temp;
}
int calcComplex(string a,string b){
	int ret;
	if (a=="n"){
		if (b=="n") ret=0;
		else ret=ZERO;
	}else {
		if (b=="n") ret=1;
		else {
			int ai=str2int(a);
			int bi=str2int(b); 
			if (ai<=bi) ret=0;
			else ret=ZERO;
		}
	}
	return ret;
}
int main(){
	string s;
	stringstream ss;
	fin>>T;
	for(int i=0;i<T;i++){
		fin>>progSizes[i]>>progComplexs[i];
		getline(fin,s);
		for(int j=0;j<progSizes[i];j++) {
			getline(fin,s);
			progs[i].push_back(s);
		}
	}
	for(int i=0;i<T;i++){
		memset(flag,false,sizeof(flag)); 
		while(!varStack.empty()) varStack.pop();
		while(!complexStack.empty()) complexStack.pop();
		complexStack.push(0); 
		int maxw=0;
		bool err=false;
		for(int j=0;j<progSizes[i];j++) {
			ss.clear();//字符串流清空 
			ss.str(progs[i][j]);//把第i个程序的第j行放入字符串流中 
			char op;
			ss>>op;
			if (op=='F'){
				char var;
				ss>>var;
				if (flag[var-'a']) err=true;
				else{
					varStack.push(var);
					flag[var-'a']=true;
					string a,b;
					ss>>a>>b;
					int curComplex=calcComplex(a,b);
					int sumComplex=complexStack.top();
					sumComplex+=curComplex;
					if (sumComplex>maxw) maxw=sumComplex;
					complexStack.push(sumComplex);
				}
			}else if (op=='E'){
				if (varStack.empty()) err=true;
				else {
					char var=varStack.top();
					flag[var-'a']=false;
					varStack.pop();
					complexStack.pop();
				}
			}else err=true;
			if (err) break;
		}
		if (varStack.size()>0)  err=true;
		if (err) fout<<"ERR"<<endl;
		else {
			string complex_string="";
			if (maxw>0) complex_string="O(n^"+int2str(maxw)+")";
			else complex_string="O(1)";
			if (complex_string==progComplexs[i]) fout<<"Yes"<<endl;
			else fout<<"No"<<endl;
		}
	}
}

