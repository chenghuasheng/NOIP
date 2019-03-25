#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
ifstream fin("load.in");
ofstream fout("load.out");


struct Region{
	long a,b;
	int deep_dec; 
};
struct Area{
	long id;
	int deep;
	bool operator<(const Area& other) const
    {
        return deep > other.deep; //Ð¡¶¥¶Ñ
    }
};
long n;
long days;
vector<Region> regions; 
priority_queue<Area> PQ;

int main(){
	fin>>n;
	for(long i=1;i<=n;i++) {
		int a;
		fin>>a;
		Area area={i,a};
		PQ.push(area);
	}
	days=0;
	Region reg={1,n,0};
	regions.push_back(reg);
	while(!PQ.empty()){
		Area area=PQ.top();
		PQ.pop();
		long i;
		for(i=0;i<regions.size();i++){
			if (regions[i].a<=area.id&&area.id<=regions[i].b) break;
		}
		if (i<regions.size()){
			if (area.deep-regions[i].deep_dec>0) days+=area.deep-regions[i].deep_dec;
			Region reg1={regions[i].a,area.id-1,area.deep};
			Region reg2={area.id+1,regions[i].b,area.deep};
			regions.erase(regions.begin()+i);
			if (reg1.a<=reg1.b) regions.push_back(reg1);
			if (reg2.a<=reg2.b) regions.push_back(reg2); 
		}
	}
	cout<<days<<endl;
}
