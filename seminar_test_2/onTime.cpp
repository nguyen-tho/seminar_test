// schedule2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

int n;
struct job {
    int time;
    int completeTime;
    bool onTime = false;
};

job J[1000];
char split;

void getData() {
    ifstream IF("jobs.inp");
    IF >> n;
    for (int i = 0; i < n; i++) {
        IF >> split >> J[i].time >> split >> J[i].completeTime >> split >> split;
    }
}

void mergeTime(job* array, int l, int m, int r) {
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
        if (larr[i].time <= rarr[j].time) {
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

void mergeSortTime(job* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortTime(array, l, m);
        mergeSortTime(array, m + 1, r);
        mergeTime(array, l, m, r);
    }
}

void jobSchedule(job* array, int size) {
    mergeSortTime(array, 0, size - 1);
    int currentTime = 0;
    for (int i = 0; i < size; i++) {
        currentTime += array[i].time;
        if (array[i].completeTime >= currentTime) {
            array[i].onTime = true;
        }
    }

    //Get result
    cout << "\n----- Schedule -----\n";
    for (int i = 0; i < size; i++) {
        cout << "(" << array[i].time << "; " << array[i].completeTime << ") | ";
        if (array[i].onTime) {
            cout << "On Time.\n";
        }
        else {
            cout << "Late.\n";
        }
    }
}
int main()
{
    getData();
    
    //Get input
    for (int i = 0; i < n; i++) {
        cout << J[i].time << " " << J[i].completeTime << "\n";
    }

    jobSchedule(J, n);
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