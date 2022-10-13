// schedule.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

struct subject {
    int start;
    int end;
    int totalTime;
};

int n;
subject S[1000];
subject choose[1000];
char split;

void getData() {
    ifstream IF("intersaction.inp");
    IF >> n;

    for (int i = 0; i < n; i++) {
        IF >> S[i].start >> S[i].end >> split;
        S[i].totalTime = abs(S[i].start - S[i].end);
    }
}
void mergeStart(subject* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    subject* larr = new subject[nl];
    subject* rarr = new subject[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].start <= rarr[j].start) {
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

void mergeSortStart(subject* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortStart(array, l, m);
        mergeSortStart(array, m + 1, r);
        mergeStart(array, l, m, r);
    }
}

void mergeTime(subject* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    subject* larr = new subject[nl];
    subject* rarr = new subject[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].totalTime <= rarr[j].totalTime) {
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

void mergeSortTime(subject* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortTime(array, l, m);
        mergeSortTime(array, m + 1, r);
        mergeTime(array, l, m, r);
    }
}

void mergeEnd(subject* array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1; nr = r - m;
    subject* larr = new subject[nl];
    subject* rarr = new subject[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0; j = 0; k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i].end <= rarr[j].end) {
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

void mergeSortEnd(subject* array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSortEnd(array, l, m);
        mergeSortEnd(array, m + 1, r);
        mergeEnd(array, l, m, r);
    }
}

void setUpSchedule1(subject* array, subject* c, int size) {
    mergeSortStart(array, 0, size - 1);
    int idx = 0;
    c[idx] = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i].start >= c[idx].end) {
            idx++;
            c[idx] = S[i];
        }
    }

    //Get result
    cout << "Result: \n";
    for (int i = 0; i <= idx; i++) {
        cout << c[i].start << " " << c[i].end << " " << "\n";
    }
}

void setUpSchedule2(subject* array, subject* c, int size) {
    mergeSortTime(array, 0, size - 1);
    int idx = 0;
    c[idx] = S[0];
    int temp;

    for (int i = 1; i < size; i++) {
        for (int j = 0; j <= idx; j++) {
            if ((array[i].start > c[j].start && array[i].start < c[j].end) ||
                (array[i].end > c[j].start && array[i].end < c[j].end) ||
                (array[i].start <= c[j].start && array[i].end >= c[j].end)) {
                temp = -1;
                break;
            }
            else {
                temp = i;
            }
        }
        if (temp != -1) {
            idx++;
            c[idx] = array[temp];
        }
    }

    //Get result
    cout << "Result: \n";
    for (int i = 0; i <= idx; i++) {
        cout << c[i].start << " " << c[i].end << " " << "\n";
    }
}

void setUpSchedule3(subject* array, subject* c, int size) {
    mergeSortEnd(array, 0, size - 1);
    int idx = 0;
    c[idx] = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i].start >= c[idx].end) {
            idx++;
            c[idx] = array[i];
        }
    }

    //Get result
    cout << "Result: \n";
    for (int i = 0; i <= idx; i++) {
        cout << c[i].start << " " << c[i].end << " " << "\n";
    }
}
int main()
{
    getData();
    
    //Check input
    cout<<"start \t end \t total time \n";
    for (int i = 0; i < n; i++) {
        cout << S[i].start << " \t" << S[i].end << " \t" << S[i].totalTime << "\n";
    }

    cout << "\n----- Greedy 1 -----\n";
    setUpSchedule1(S, choose, n);
    cout << "\n----- Greedy 2 -----\n";
    setUpSchedule2(S, choose, n);
    cout << "\n----- Greedy 3 -----\n";
    setUpSchedule3(S, choose, n);

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