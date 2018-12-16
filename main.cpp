/************************************************
Jason Schilling
11/15/2018
COT4400 Programming Assignment
Quick and dirty implementation of the Insertion Sort, Quick Sort, and Heap Sort algorithms.
Outputed data to be analyzed.
HAVE FUN!!!
************************************************/

// INCLUDES
#include <stdlib.h>
#include <iostream>
#include <time.h>

using namespace std;

// FUNCTION DECLARATIONS
void insertionSort(int[], int);
void printArray(int[], int);
void quickSort(int[], int, int);
int partition(int[], int, int);
void heapSort(int[], int);
void maxHeapify(int[], int, int);
void buildMaxHeap(int[], int n);
void swap(int, int, int[]);
int right(int);
int left(int);

int main()
{
	clock_t started, ended;

	// make separate arrays for each algorithm data
	int arr1[50000];
	int arr2[50000];
	int arr3[50000];

	// make arrays of different sizes, fill with random values, and run all algorithms for each size
	for (int i = 1000; i <= 50000; i += 1000) {
		double arr1Avg = 0, arr2Avg = 0, arr3Avg = 0;
		// 5 trials for each size
		for (int k = 0; k < 5; k++) {
			for (int j = 0; j < i; j++) {
				arr1[j] = arr2[j] = arr3[j] = rand();
			}
			started = clock();
			insertionSort(arr1, i);
			ended = clock();
			arr1Avg += ended - started;
			started = clock();
			quickSort(arr2, 0, i - 1);
			ended = clock();
			arr2Avg += ended - started;
			started = clock();
			heapSort(arr3, i);
			ended = clock();
			arr3Avg += ended - started;
		}

		// Take average of 5 trials
		arr1Avg /= 5;
		arr2Avg /= 5;
		arr3Avg /= 5;

		// OUTPUT
		cout << "---------------------------------------\n";
		cout << "AVERAGES FOR N = " << i;
		cout << "\n---------------------------------------\n";
		cout << "INSERTION SORT: " << arr1Avg << "\n\n\n";
		cout << "QUICK SORT: " << arr2Avg << "\n\n\n";
		cout << "HEAP SORT: " << arr3Avg << "\n\n\n";
	}

	system("pause");

	return 0;
}

// Insertion Sort
void insertionSort(int elements[], int n)
{
	int current, temp;
	for (int i = 1; i < n; i++)
	{
		current = elements[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (elements[j] > current)
			{
				temp = elements[j];
				elements[j] = current;
				elements[j+1] = temp;
			}
		}
	}
}

// Quick Sort
void quickSort(int a[], int left, int right) {
	int index = partition(a, left, right);
	if (left < index - 1)
		quickSort(a, left, index - 1);
	if (index < right)
		quickSort(a, index, right);
}

// Helper function for Quick Sort
int partition(int a[], int left, int right) {
	int i = left, j = right;
	int tmp;
	int pivot = a[(left + right) / 2];
	while (i <= j) {
		while (a[i] < pivot) i++;
		while (a[j] > pivot) j--;
		if (i <= j) {
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
	}
	return i;
}

// Heap Sort
void heapSort(int arr[], int n) {
	buildMaxHeap(arr, n);
	for (int i = n-1; i > 0; i--) {
		swap(0, i, arr);
		maxHeapify(arr, i, 0);
	}
}

// Helper functions for Heap Sort ////////////////////////////////////////////////////
void maxHeapify(int arr[], int n, int i) {
	int leftChildIndex = left(i);
	int rightChildIndex = right(i);
	int indexOfLargest;
	if (leftChildIndex < n && arr[leftChildIndex] > arr[i]) {
		indexOfLargest = leftChildIndex;
	}
	else {
		indexOfLargest = i;
	}
	if (rightChildIndex < n && arr[rightChildIndex] > arr[indexOfLargest]) {
		indexOfLargest = rightChildIndex;
	}
	if (indexOfLargest != i) {
		swap(i, indexOfLargest, arr);
		maxHeapify(arr, n, indexOfLargest);
	}
}

void buildMaxHeap(int arr[], int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		maxHeapify(arr, n, i);
	}
}

int left(int i) {
	return (2 * i) + 1;
}

int right(int i) {
	return 2 * (i + 1);
}

void swap(int i, int j, int arr[]) {
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}
// END OF HEAP SORT HELPER FUNCTIONS //////////////////////////////////////////////////////