#include<iostream>
#include<limits.h>
#include<fstream>
using namespace std;
#define MAX 100

int matrix[MAX][MAX];
int n;
int p;
int V[MAX];
int flag[MAX];
int tour[MAX+1][MAX+1];
int mCost[MAX+1];
int cost;
int cs;


void getInput(){
    ifstream fi;
    fi.open("GTS2.inp");
    if(fi.bad()){
        cout<<"File Doesn't Exist";
    }
    fi>>n>>p;
    for(int i = 1; i <= p; i++){
        fi>>V[i];
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            fi>>matrix[i][j];
        }
    
    
    fi.close();
}

int GTS1(int v){
    for(int i = 1; i <=n; i++){
        flag[i] = 0;
    }
    
    int t = v;
    int count = 0;
    tour[t][0] = v;
    cost = 0;
    flag[v] = 1;
    int temp = v;
    while(count != n-1){
        int tmpCost = INT_MAX;
        int co;
        for(int i = 1; i <= n; i++){
            if(tmpCost > matrix[v][i] && flag[i] == 0 && matrix[v][i] != 0){
                tmpCost = matrix[v][i];
                co = i;
            }
        }

        count++;
        tour[t][count] = co;
        cost += tmpCost;
        flag[v] = 1;
        v = co;
    }
    cost += matrix[v][t];
    mCost[t] = cost;

    return cost;
}

int GTS2(){
    int temp = INT_MAX;
    int a[p];
    int i;
    for(i=1 ; i <= p; i++){
        a[i] = GTS1(V[i]);
       temp = min(temp, a[i]);
    }
    return i;
}

void getOutput(){
    cs = GTS2();
    cout<<"Total cost for tour: "<<mCost[cs]<<"\n";
    cout<<"Path: ";
    for(int i = 0; i < n; i++){
        cout<<tour[cs][i]<<"-->";
    }
    cout<<tour[cs][0]<<"\n";
}

int main(){
    getInput();
    GTS2();
    getOutput();
    return 0;
}




