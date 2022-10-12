// johnson.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <algorithm>
#include <fstream>

using namespace std;

int n;

struct job {
    int id;
    int time_on_A;
    int time_on_B;
};

job J[1000];

void getData() {
    ifstream IF;
    IF.open("Johnson.inp");
    if(IF.bad()){
        cout<<"File Doesn't Exist";
    }
    IF >> n;
    for (int i = 0; i < n; i++) {
        J[i].id = i;
        IF >> J[i].time_on_A;
    }
    for (int i = 0; i < n; i++) {
        IF >> J[i].time_on_B;
    }

    IF.close();
}

job N1[1000], N2[1000];
int i1 = 0, i2 = 0;

void mergeN1(job* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    job* larr = new job[nl];
    job* rarr = new job[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].time_on_A <= rarr[j].time_on_A) {
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

void mergeSortN1(job* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortN1(array, l, m);
        mergeSortN1(array, m + 1, r);
        mergeN1(array, l, m, r);
    }
}

void mergeN2(job* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    job* larr = new job[nl];
    job* rarr = new job[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].time_on_B >= rarr[j].time_on_B) {
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

void mergeSortN2(job* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortN2(array, l, m);
        mergeSortN2(array, m + 1, r);
        mergeN2(array, l, m, r);
    }
}

job res[1000]; //Contain job list to do
void johnson_algorithm() {
    for (int i = 0; i < n; i++) {
        if (J[i].time_on_A <= J[i].time_on_B) {
            N1[i1] = J[i];
            i1++;
        }
        else {
            N2[i2] = J[i];
            i2++;
        }
    }

    mergeSortN1(N1, 0, i1 - 1);
    mergeSortN2(N2, 0, i2 - 1);

    //Result
    int i = 0;

    while (true) {
        for (int idx = 0; idx < i1; idx++) {
            res[i] = N1[idx];
            i++;
        }
        for (int idx = 0; idx < i2; idx++) {
            res[i] = N2[idx];
            i++;
        }
        break;
    }
}
int main()
{
    getData();
    johnson_algorithm();
    cout << "Result: ";
    for (int i = 0; i < n; i++) {
        cout << (res[i].id) + 1 << " ";
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file