//
// Created by Hamidou Wara Ballo on 5/18/20.
//

#ifndef SORTING_ANALYSIS_SORTING_H
#define SORTING_ANALYSIS_SORTING_H
void initializeCounters();
void resetCounters();
void swap(int *xp, int *yp);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void makeHeap(int arr[], int n, int i);
void heapSort(int arr[], int n);
void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void initializeArray(int arr[], int size, int flag);
void copyArray(int arr1[], int arr2[], int size);
void runSimulation(int flag, int size);
void printCounters(int flag, int size);
#endif //SORTING_ANALYSIS_SORTING_H
