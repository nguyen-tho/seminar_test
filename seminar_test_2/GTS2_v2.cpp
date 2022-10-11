#include<iostream>
#include<limits.h>
#include<fstream>
using namespace std;
#define MAX 100

int matrix[MAX][MAX];
int n;
int p = 6;
int V[]= {2,3,5,6};


struct result
{
    int Btour[MAX+1];
    int Bcost;
};


void getInput(){
    ifstream fi;
    fi.open("GTS1.inp");
    if(fi.bad()){
        cout<<"File Doesn't Exist";
    }
    fi>>n;
    /*
    for(int k = 1; k <= p; k++){
        fi>>V[k];
    }*/
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++){
            fi>>matrix[i][j];
        }

    fi.close();
}
void copyArr(int src[],int des[]){
    
   for(int i = 0; i < n; i++){
        des[i] = src[i];
    }
    des[n] = src[0];
}

result GTS1(int v){
    int flag[n+1];
    int tour[n+1];
    int cost;
    result res;

    for(int i = 0; i <=n; i++){
        flag[i] = 0;
    }

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
    res.Bcost = cost;
    copyArr(tour, res.Btour);
    return res;

}

int GTS2(){

    result res[p];
    int temp = INT_MAX;
    int choosen;
    for(int i = 1; i <= p; i++){
        res[i] = GTS1(i);
        if(temp > res[i].Bcost){
            temp = res[i].Bcost;
            choosen = i;
        }
    }
       
    return choosen;
}

void getOutput(){
    result res = GTS1(GTS2());
    cout<<"Total cost for tour: "<<res.Bcost<<"\n";
    cout<<"Path: ";
    for(int i = 0; i < n; i++){
        cout<<res.Btour[i]<<"-->";
    }
    cout<<res.Btour[0]<<"\n";
}

int main(){
    getInput();
    getOutput();
    return 0;
}
