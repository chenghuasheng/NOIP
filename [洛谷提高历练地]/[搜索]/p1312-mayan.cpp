#include <iostream>
using namespace std;

struct State{
    int cells[7][5]={{0}};
    bool can[7][5]={{false}};
    bool isover(){
        for(int j=0;j<5;j++) 
            if (cells[0][j]>0) return false;
        return true;
    }
    bool clearup(){
        bool ret=false;
        for(int i=0;i<7;i++)
            for(int j=0;j<5;j++) {
                if (cells[i][j]==0) continue;
                if (j>=2&&cells[i][j]==cells[i][j-1]&&cells[i][j]==cells[i][j-2]){
                    can[i][j]=can[i][j-1]=can[i][j-2]=true;
                    ret=true;
                }
                if (i>=2&&cells[i][j]==cells[i-1][j]&&cells[i][j]==cells[i-2][j]){
                    can[i][j]=can[i-1][j]=can[i-2][j]=true;
                    ret=true;
                }
        }
        
        if (ret){
            for(int i=0;i<7;i++){
                for(int j=0;j<5;j++)
                    if (can[i][j]) {
                        cells[i][j]=0;
                        can[i][j]=false;
                    }
            }
        }
        return ret;
    }
    void falldown(){
        for(int j=0;j<5;j++){
            int num=0;
            for(int i=0;i<7;i++)
                if (!cells[i][j]) num++;
                else{
                    if (num>0){
                        cells[i-num][j]=cells[i][j];
                        cells[i][j]=0;
                    }
                }   
        }
    }
};
struct Action{
    int i,j,d;
};

int off[2]={1,-1};
int n;
State s;
Action actions[5];
void dfs(State state,int level){
    if (state.isover()){
        for(int k=0;k<level;k++) 
            cout<<actions[k].j<<' '<<actions[k].i<<' '<<actions[k].d<<endl;
        exit(0);
    }else {
        if (level>=n) return;
        for(int j=0;j<5;j++){
            for(int i=0;i<7;i++){
                if (state.cells[i][j]==0) break;
                for(int d=0;d<2;d++){
                    int newj=j+off[d];
                    if (newj<0||newj>=5) continue;
                    if (off[d]==-1&&state.cells[i][newj]>0) continue;//去掉重复动作
                    State nextState=state;
                    swap(nextState.cells[i][j],nextState.cells[i][newj]);
                    do{
                        nextState.falldown();
                    }while(nextState.clearup());
                    actions[level]={i,j,off[d]};
                    dfs(nextState,level+1);
                }
            }
        }
    }
}
int main(){
    cin>>n;
    for(int j=0;j<5;j++){
        int a;
        int i=0;
        do{
            cin>>a;
            if (a>0){
                s.cells[i][j]=a;
                i++;
            }
        }while(a>0);
    }
    dfs(s,0);
    cout<<-1;
}