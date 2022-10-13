// assignment2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits.h>
#include <math.h>
#include <fstream>

using namespace std;

int n;

struct job {
    int id;
    int time;
};
struct machine {
    int id;
    int total = 0;
    job jobs[1000];
    int total_time = 0;
};
machine M[3];
job J[1000];
int L[1000];
int totalTime = 0;

void getData() {
    ifstream IF("assignment3_b.inp");
    IF >> n;
    for (int i = 0; i < n; i++) {
        J[i].id = i;
        IF >> J[i].time;
    }
    for (int i = 0; i < n; i++) {
        int temp;
        IF >> temp;
        L[i] = temp - 1;
    }
}

void merge(job* array, int l, int m, int r) {
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
        if (larr[i].time >= rarr[j].time) {
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

void mergeSort(job* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}
void getOutput(){
     for (int i = 0; i < 3; i++) {
        if (M[i].total_time > totalTime) totalTime = M[i].total_time;
        cout << "M" << i + 1 << ": {";
        for (int j = 0; j < M[i].total; j++) {
            cout <<"J("<< (M[i].jobs[j].id) + 1<<")" << " ";
        }
        cout << "}\n";
    }
    cout << "Total time to complete is " << totalTime;
}
void assignment2() {
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < n) {
            if (J[j].id == L[i]) {
                int minT = INT_MAX;
                int next = -1;
                for (int m = 0; m < 3; m++) {
                    if (M[m].total_time < minT) {
                        minT = M[m].total_time;
                        next = m;
                    }
                }
                M[next].total++;
                int idx = M[next].total - 1;
                M[next].jobs[idx] = J[j];
                M[next].total_time += J[j].time;
            }
            j++;
        }
    }

    //Result
    getOutput();
}
/*
void assignment2_2() {
    int j = 0;
    while (j < n) {
        int minT = INT_MAX;
        int next = -1;
        for (int m = 0; m < 3; m++) {
            if (M[m].total_time < minT) {
                minT = M[m].total_time;
                next = m;
            }
        }
        M[next].total++;
        int idx = M[next].total - 1;
        M[next].jobs[idx] = J[j];
        M[next].total_time += J[j].time;
        j++;
    }

    //Result
    for (int i = 0; i < 3; i++) {
        if (M[i].total_time > totalTime) totalTime = M[i].total_time;
        cout << "M" << i << ": {";
        for (int j = 0; j < M[i].total; j++) {
            cout << M[i].jobs[j].id << " ";
        }
        cout << "}\n";
    }
    cout << "Total time to complete is " << totalTime;
}*/
int main()
{
    //2A
    getData();
    assignment2();

    //2B
    /*getData("assignment2_2.inp");
    mergeSort(J, 0, n - 1);
    assignment2_2();*/
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