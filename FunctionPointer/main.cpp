/*
 * File:   main.cpp
 * Author: Vareto
 *
 * Created on January 22, 2015, 3:43 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

void bubble(int [], const int, bool (*) (int, int));
bool ascending(const int, const int);
bool descending(const int, const int);

int main(int argc, char** argv) {
    const int arraySize = 10;
    int order,
            counter,
            a[arraySize] = {2, 6, 4, 8, 10, 12, 89, 68, 45, 37};

    cout << "Type 1 for ascending sorting, \n"
            << "Type 2 for descending sorting: ";
    cin >> order;

    cout << "\nOriginal Order\n";
    for (counter = 0; counter < arraySize; counter++)
        cout << setw(4) << a[counter];

    if (order == 1) {
        bubble(a, arraySize, ascending);
        cout << "\nAscending Order\n";
    } else {
        bubble(a, arraySize, descending);
        cout << "\nDescending Order\n";
    }

    for (counter = 0; counter < arraySize; counter++)
        cout << setw(4) << a[counter];

    return 0;
}

void bubble(int work[], const int size, bool (*compare) (int, int)) {
    void swap(int * const, int * const); //method swap cannot call method bubble

    for (int pass = 1; pass < size; pass++) {
        for (int count = 0; count < size - 1; count++) {
            if ((*compare) (work[count], work[count + 1])) {
                swap(&work[count], &work[count + 1]);
            }
        }
    }
}

void swap(int * const element1Ptr, int * const element2Ptr) {
    int temp = *element1Ptr;
    *element1Ptr = *element2Ptr;
    *element2Ptr = temp;
}

bool ascending(const int a, const int b) {
    return a > b; //Swap if a is greater than b
}

bool descending(const int a, const int b) {
    return a < b; //Swap if a is lesser than b
}