// typing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int n;

struct book {
    int id;
    int nop;
    int eTime;
    int mTime;
};
struct typer {
    int total = 0;
    book books[1000];
    int time = 0;
};
book B[1000];
typer E[3];
typer manager;

int totalTime = 0;

void getData() {
    ifstream IF("typing.inp");
    IF >> n;
    for (int i = 0; i < n; i++) {
        B[i].id = i;
        IF >> B[i].nop;
        B[i].eTime = B[i].nop / 10;
        B[i].mTime = B[i].eTime * 3 / 2;
    }
}

void merge1(book* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    book* larr = new book[nl];
    book* rarr = new book[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].eTime >= rarr[j].eTime) {
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

void mergeSort1(book* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSort1(array, l, m);
        mergeSort1(array, m + 1, r);
        merge1(array, l, m, r);
    }
}

void typing_assignment1() {
    mergeSort1(B, 0, n - 1);
    for (int i = 0; i < n; i++) {
        int minT = INT_MAX;
        int next = -1;
        for (int m = 0; m < 3; m++) {
            if (E[m].time < minT) {
                minT = E[m].time;
                next = m;
            }
            if (m == 2) {
                E[next].total++;
                int idx = E[next].total - 1;
                E[next].books[idx] = B[i];
                E[next].time += B[i].eTime;
            }
        }
    }

    //Result
    for (int i = 0; i < 3; i++) {
        if (E[i].time > totalTime) totalTime = E[i].time;
        cout << "E" << i << ": {";
        for (int j = 0; j < E[i].total; j++) {
            cout << E[i].books[j].id << " ";
        }
        cout << "}\n";
    }
    cout << "Total time to complete is " << totalTime;
    cout << "\n";
}

void typing_assignment2() {
    mergeSort1(B, 0, n - 1);
    for (int i = 0; i < n; i++) {
        int minT = INT_MAX;
        int next = -1;
        for (int m = 0; m < 3; m++) {
            if (E[m].time < minT) {
                minT = E[m].time;
                next = m;
            }
            if (m == 2) {
                if (manager.time < minT) {
                    minT = manager.time;
                    manager.total++;
                    int idx = manager.total - 1;
                    manager.books[idx] = B[i];
                    manager.time += B[i].mTime;
                    break;
                }
                E[next].total++;
                int idx = E[next].total - 1;
                E[next].books[idx] = B[i];
                E[next].time += B[i].eTime;
            }
        }
    }

    //Result
    for (int i = 0; i < 3; i++) {
        if (E[i].time > totalTime) totalTime = E[i].time;
        cout << "E" << i << ": {";
        for (int j = 0; j < E[i].total; j++) {
            cout << E[i].books[j].id << " ";
        }
        cout << "}\n";
    }

    if (manager.time > totalTime) totalTime = manager.time;
    cout << "M: " << ": {";
    for (int j = 0; j < manager.total; j++) {
        cout << manager.books[j].id << " ";
    }
    cout << "}\n";

    cout << "Total time to complete is " << totalTime;
    cout << "\n";
}

int main()
{
    getData();
    typing_assignment1();
    
    //typing_assignment2();
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