#include<iostream>
#include<fstream>
#include<limits.h>

#define MAX 100

using namespace std;

int n;
int w[MAX][MAX];
bool assigned[MAX];
int cost = 0;
struct asmt{
    int worker;
    int job;
};
asmt A[MAX];
void getInput(){
    ifstream fi;
    fi.open("assignment.inp");

    fi>>n;
    for(int i = 0; i < n; i++){
        A[i].worker = i;
        for(int j = 0; j < n; j++){
            fi>>w[i][j];
            assigned[j] = false;
        }
    }

    fi.close();
}

int* copyRow(int row){
    int arr[n];
    for(int i = 0; i < n; i++){
        arr[i] = w[row][i];
    }
    return arr;

}

int maxEff(int arr[]){
    int max = INT_MIN;
    int i;
    int t;
    for( i = 0; i < n; i++){
        if(arr[i] > max && !assigned[i]){
            max = arr[i];
            t = i;
        }
    }
    assigned[t] = true;
    cost += max;
    return t;
}

void assignment(){
    for(int i = 0; i < n; i++){
        int* worker = copyRow(i);
        int effJob = maxEff(worker);
        A[i].job = effJob;   
    }
}

void getOutPut(){
    /*
    cout<<"Assignment matrix\n";
    for(int i = 0; i < n; i++){       
        for(int j = 0; j < n; j++){
            cout<<w[i][j]<<" ";
        }
        cout<<"\n";
    }
    */
    for(int i = 0; i < n; i++){
        cout << "Worker " << A[i].worker << " was assigned job " << A[i].job<<"\n";
    }

    cout<< "Most value: "<< cost;
}
int main(){
    getInput();
    assignment();
    getOutPut();
    
    return 0;
}