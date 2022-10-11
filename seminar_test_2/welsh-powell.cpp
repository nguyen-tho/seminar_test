// greedy_coloring_problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

using namespace std;

#define SIZE int(1E3)
int n;
int G[SIZE][SIZE];
int color = 1;

struct ver
{
    int v;
    int deg;
    int color_val;
    bool colored = false;
};

ver V[SIZE];
void getInput(){
	ifstream IF ("color2.inp");
    IF >> n;
    
    for (int i = 0; i < n; i++) {
        V[i].v = i;
        for (int j = 0; j < n; j++) {
            IF >> G[i][j];
            if (G[i][j] == 1) {
                V[i].deg += 1;
            }
        }           
    }
	IF.close();
}
int takeColorAmount(ver *arr, int size){
	int color = 0;
	for(int i = 0; i < size; i++){
		if(arr[i].color_val > color){
			color = arr[i].color_val;
		}
	}
	return color;
}

void display_color(ver* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << "(V" << arr[i].v << ", deg = " << arr[i].deg << "): " << arr[i].color_val << "\n";
    }
}

void merge(ver* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    ver* larr = new ver [nl];
    ver* rarr = new ver [nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].deg >= rarr[j].deg) {
            array[k] = larr[i];
            i++;
        }
        else {
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {       //extra element in left array
        array[k] = larr[i];
        i++; k++;
    }
    while (j < nr) {     //extra element in right array
        array[k] = rarr[j];
        j++; k++;
    }
}

void mergeSort(ver* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

void ver_colored(ver _ver) {
    _ver.color_val = color;
    _ver.colored = true;
    for (int j = 0; j < n; j++) {
        int vi = _ver.v;
        int vj = V[j].v;
        if (G[vi][vj] == 0 && !V[j].colored) {
            V[j].color_val = color;
            V[j].colored = true;
        }
    }
}

void coloring() {
    for (int i = 0; i < n-1; i++) {
        if (!V[i].colored) {
            ver_colored(V[i]);
            color++;
        }
    }
}

int main()
{    
    // Doc ma tran ke tu file
    getInput();

    mergeSort(V, 0, n - 1);

    coloring();
    display_color(V, n);

    cout << "Number of color: " << takeColorAmount(V, SIZE);

    
    return 0;
}

