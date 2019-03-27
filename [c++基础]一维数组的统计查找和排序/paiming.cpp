#include <iostream>
#include <algorithm>
using namespace std;

struct student{
	int score,grade;
}; 
bool compare(student a, student b) {
		if (a.score>b.score) return true;
		else if (a.score==b.score&&a.grade<b.grade) return true;
		else return false;
}

const int MAXN=200;
student stus[MAXN];
int n;

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>stus[i].score>>stus[i].grade; 
	}
	sort(stus,stus+n,compare);
	for(int i=0;i<n;i++){
		int k=0;
		for (int j=0;j<i;j++){
			if (stus[j].grade<stus[i].grade) k++;
		}
		cout<<k<<endl;
	}
}