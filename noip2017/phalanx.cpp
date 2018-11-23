#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
ifstream fin("phalanx.in");
ofstream fout("phalanx.out");
const long MAXINT=300000;
long n,m,q;
struct Region{
	long start,end;
	long count;
	Region* left;
	Region* right;
	Region* parent;
};

Region* horiSegTrees[300000];
Region* vertSegTree;
vector<long long> horiQueues[300000];
vector<long long> vertQueue;
long x[300000],y[300000]; 

void remove(Region* segTree,long k){
	segTree->count++;
	if (segTree->start<segTree->end){
		long mid=(segTree->start+segTree->end)/2;
		if (segTree->start+k<=mid){
			segTree->left=new Region;
			*(segTree->left)={segTree->start,mid,0,NULL,NULL,segTree};
			remove(segTree->left,k);
		}else {
			segTree->right=new Region;
			*(segTree->right)={mid+1,segTree->end,0,NULL,NULL,segTree};
			remove(segTree->right,k+segTree->start-mid-1);
		}
	}
}
long findAndRemove(Region* segTree,long k){
	if (segTree->count==0) {
		long ret=segTree->start+k;
		remove(segTree,k);
		Region* p=segTree->parent; 
		while(NULL!=p){
			p->count++;
			p=p->parent;
		}
		return ret;
	}else{
		Region* leftTree=segTree->left;
		Region* rightTree=segTree->right;
		if (NULL!=leftTree){
			long num=leftTree->end-leftTree->start+1-leftTree->count;
			if (k+1<=num) return findAndRemove(leftTree,k);
			else if (NULL!=rightTree) return findAndRemove(rightTree,k-num);
			else {
				segTree->right=new Region;
				*(segTree->right)={leftTree->end+1,segTree->end,0,NULL,NULL,segTree};
				return findAndRemove(segTree->right,k-num);
			}
		}else {
			if (NULL!=rightTree) {
				long num=rightTree->start-segTree->start;
				if (k+1<=num){
					segTree->left=new Region;
					*(segTree->left)={segTree->start,rightTree->start-1,0,NULL,NULL,segTree};
					return findAndRemove(segTree->left,k);
				}else return findAndRemove(rightTree,k-num);
			}else return -1;
		}
	}
}

void append(Region* segTree){
	if (segTree->start<segTree->end) {
		segTree->end++;
		if (NULL!=segTree->right) append(segTree->right);
	}else {
		if (segTree->count==0){
			segTree->end++;
			if (NULL!=segTree->right) append(segTree->right);
		}else{
			segTree->end++;
			remove(segTree,0);
		}
	} 
}
//void display(Region* segTree,string pref){
//	cout<<pref<<" "<<segTree->start<<","<<segTree->end<<":"<<segTree->count<<endl;
//	if (NULL!=segTree->left) display(segTree->left,pref+" left");
//	if (NULL!=segTree->right) display(segTree->right,pref+" right");
//}
//void test(){
//	Region reg={0,10-1,0,NULL,NULL,NULL};
//	vertSegTree=&reg;
//	for(int i=0;i<10;i++) vertQueue.push_back(i);
//	long k=findAndRemove(vertSegTree,5);
//	long digit=vertQueue[k];
//	append(vertSegTree);
//	vertQueue.push_back(digit);
//	cout<<digit<<endl;
//	display(vertSegTree,"");
//	k=findAndRemove(vertSegTree,3);
//	digit=vertQueue[k];
//	append(vertSegTree);
//	vertQueue.push_back(digit);
//	cout<<digit<<endl;
//	display(vertSegTree,"");
//}

int main(){
	//test();
	fin>>n>>m>>q;
	long a,b;
	for(long i=0;i<q;i++){
		fin>>a>>b;
		x[i]=a-1;
		y[i]=b-1;
	}
	for(long i=0;i<n;i++){
		horiSegTrees[i]=new Region;
		*(horiSegTrees[i])={0,m-2,0,NULL,NULL,NULL};
		vertQueue.push_back(i*m+m);	
	}
	vertSegTree=new Region;
	*vertSegTree={0,n-1,0,NULL,NULL,NULL};

	for(long i=0;i<q;i++){
		long a=x[i];
		long b=y[i];
		long long digit;
		if (b==m-1){
			long k=findAndRemove(vertSegTree,a);
			digit=vertQueue[k];
			append(vertSegTree);
			vertQueue.push_back(digit);
		}else {
			long k=findAndRemove(horiSegTrees[a],b);
			if (k>m-2) digit=horiQueues[a][k-m+1];
			else digit=a*m+k+1;
			long k1=findAndRemove(vertSegTree,a);
			long long digit1=vertQueue[k1];
			append(horiSegTrees[a]);
			horiQueues[a].push_back(digit1);
			append(vertSegTree);
			vertQueue.push_back(digit);	
		}
		cout<<digit<<endl;
	}	
}
