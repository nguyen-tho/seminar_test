#include<iostream>
#include<limits.h>
#include<fstream>
using namespace std;
#define MAX 100

int matrix[MAX][MAX];
int n;
int flag[MAX+1];
int tour[MAX+1];
int cost;



void getInput(){
    ifstream fi;
    fi.open("GTS1.inp");
    if(fi.bad()){
        cout<<"File Doesn't Exist";
    }
    fi>>n;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            fi>>matrix[i][j];
        }
    
    for(int i = 0; i <=n; i++){
        flag[i] = 0;
    }

    fi.close();
}

void getOutput(){
    cout<<"Total cost for tour: "<<cost<<"\n";
    cout<<"Path: ";
    for(int i = 0; i < n; i++){
        cout<<tour[i]<<"-->";
    }
    cout<<tour[0]<<"\n";
}

void GTS1(int v){
    int count = 0;
    tour[0] = v;
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
        tour[count] = co;
        cost += tmpCost;
        flag[v] = 1;
        v = co;
    }
    cost += matrix[v][temp];
}

int main(){
    getInput();
    GTS1(4);
    getOutput();
    return 0;
}
