#include <iostream>
using namespace std;

const int MAXN=200;
int score[MAXN];
int grade[MAXN];

int n;

int main(){
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>score[i]>>grade[i]; 
	}

    for(int i=1;i<n;i++)
        for(int j=0;j<n-i;j++){
            if ((score[j]<score[j+1])||(score[j]==score[j+1]&&grade[j]>grade[j+1])){
                swap(score[j],score[j+1]);
                swap(grade[j],grade[j+1]);
            }
        }
    
    for(int i=0;i<n;i++){
		int k=0;
		for (int j=0;j<i;j++){
			if (grade[j]<grade[i]) k++;
		}
		cout<<k<<endl;
	}
    //system("pause");
}