//
// Created by Hamidou Wara Ballo on 5/18/20.
//

#include "Sorting.h"
#include<iostream>
#include<time.h>
#include<string>
#include<iomanip>
using namespace std;
#define SELECTION 0
#define INSERTION 1
#define HEAP 2
#define MERGE 3
#define QUICK 4

int Comparisons[5];
int Swaps[5];

void initializeCounters()
{
    for(int i = 0; i<5;i++)
    {
        Comparisons[i] = 0;
        Swaps[i] = 0;
    }
}

void resetCounters()
{
    for(int i = 0; i<5;i++)
    {
        Comparisons[i] = 0;
        Swaps[i] = 0;
    }
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, minIdx;

    for (i = 0; i < n-1; i++)
    {
        minIdx = i;
        for (j = i+1; j < n; j++)
        {
            Comparisons[SELECTION]++;
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        swap(&arr[minIdx], &arr[i]);
        Swaps[SELECTION]++;
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++){
        key = arr[i];
        j = i - 1;

        int temp = 0;
        Comparisons[INSERTION]++; // first update for the case where the condition is false
        while (j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j = j - 1;
            temp = 1;
            Comparisons[INSERTION]++;
        }
        if(temp == 1){
            Comparisons[INSERTION]--;
        }
        Swaps[INSERTION]++;
        arr[j + 1] = key;
    }
}

void makeHeap(int arr[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    Comparisons[HEAP]++;
    if (l < n && arr[l] > arr[largest]){
        largest = l;
    }

    Comparisons[HEAP]++;
    if (r < n && arr[r] > arr[largest])
    {
        largest = r;
    }

    if (largest != i){
        swap(arr[i], arr[largest]);
        Swaps[HEAP]++;
        makeHeap(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        makeHeap(arr, n, i);

    for (int i=n-1; i>0; i--)
    {
        Swaps[HEAP]++;
        swap(arr[0], arr[i]);
        makeHeap(arr, i, 0);
    }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        Comparisons[MERGE]++;
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        Comparisons[QUICK]++;
        if (arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
            Swaps[QUICK]++;
        }
    }
    swap(&arr[i + 1], &arr[high]);
    Swaps[QUICK]++;
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void initializeArray(int arr[], int size, int flag)
{
    srand(time(nullptr)); //seeding the randmonizer for different array every time
    int ninetyPercent = (size*90)/100;
    if(flag == 1){
        for(int i=0;i<size;i++){
            arr[i] = rand()%size;
        }
    }else if(flag == 2){
        for(int i=0;i<size;i++){
            if(i < ninetyPercent){
                arr[i] = i;
            }else{
                arr[i] = rand()%size;
            }
        }
    }else{
        for(int i=0;i<size;i++){
            arr[i] = size-i-1;
        }
    }
}

void copyArray(int arr1[], int arr2[], int size)
{
    for(int i=0;i<size;i++)
    {
        arr2[i] = arr1[i];
    }
}

void runSimulation(int flag, int size)
{
    resetCounters();
    int arrOriginal[size],arrCopy[size];

    initializeArray(arrOriginal, size, flag);

    copyArray(arrOriginal, arrCopy, size);
    selectionSort(arrCopy, size);

    copyArray(arrOriginal, arrCopy, size);
    insertionSort(arrCopy, size);

    copyArray(arrOriginal, arrCopy, size);
    heapSort(arrCopy, size);

    copyArray(arrOriginal, arrCopy, size);
    mergeSort(arrCopy, 0, size-1);

    copyArray(arrOriginal, arrCopy, size);
    quickSort(arrCopy, 0, size-1);
}

void printCounters(int flag, int size)
{
    string condition;
    int temp;
    int temp2;
    if(flag == 1){
        condition = "TOTALLY RANDOM ";
        temp = 71;
        temp2 = 75;
    }else if(flag == 2){
        condition = "90% SORTED AND 10% RANDOM";
        temp = 75;
        temp2 = 79;
    }else{
        condition = "SORTED IN REVERSE ORDER";
        temp = 79;
        temp2 = 79;
    }
    cout<<"\n"<<right<<setfill('-')<<setw(29)<<" | RESULTS FOR "<<condition<<" ARRAY OF SIZE "<<setfill(' ')<<setw(4)<<size<<" |"<<setfill('-')<<setw(14)<<"-"<<"\n";
    cout<<setfill('_')<<setw(temp)<<"_\n";
    cout<<setfill(' ')<<"Sorting Algorithm"<<setw(25)<<"Number of Comparisons"<<setw(25)<<"Number of Swaps\n";
    cout << left << setw(24) << "Selection Sort" << setw(27) << Comparisons[SELECTION] << setw(25) << Swaps[SELECTION] << "\n";
    cout << left << setw(24) << "Insertion Sort" << setw(27) << Comparisons[INSERTION] << setw(25) << Swaps[INSERTION] << "\n";
    cout << left << setw(24) << "Heap Sort" << setw(27) << Comparisons[HEAP] << setw(25) << Swaps[HEAP] << "\n";
    cout << left << setw(24) << "Merge Sort" << setw(27) << Comparisons[MERGE] << setw(25) << Swaps[MERGE] << "\n";
    cout << left << setw(24) << "Quick Sort" << setw(27) << Comparisons[QUICK] << setw(25) << Swaps[QUICK] << "\n";
    cout<<right<<setfill('_')<<setw(temp2)<<"_\n";
}
