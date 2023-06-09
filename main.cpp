#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

// Define the size of the array
const int NUMBERS_SIZE = 50000;

// Define the number of clock ticks per millisecond
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

// Function to swap two elements in an array
void Swap(int numbers[], int i, int j) {
    int temp = numbers[i]; // Temporarily store the i-th number
    numbers[i] = numbers[j]; // Replace the i-th number with the j-th number
    numbers[j] = temp; // Replace the j-th number with the temp (original i-th number)
}

// Quicksort function that uses the midpoint as the pivot
void Quicksort_midpoint(int numbers[], int i, int k) {
    if (i >= k) {
        return; // If the left index i is greater than or equal to the right index k, stop the recursion
    }

    // Choose the pivot to be the midpoint of the array
    int pivot = numbers[i + (k - i) / 2];
    int left = i;
    int right = k;

    // Partition the array
    while (left <= right) {
        // Increment left index while numbers on the left are less than the pivot
        while (numbers[left] < pivot) {
            left++;
        }

        // Decrement right index while numbers on the right are greater than the pivot
        while (numbers[right] > pivot) {
            right--;
        }

        // If the left index is less than or equal to the right index, swap the corresponding numbers
        if (left <= right) {
            Swap(numbers, left, right);
            left++;
            right--;
        }
    }

    // Recursively apply the function to the left and right halves of the array
    Quicksort_midpoint(numbers, i, right);
    Quicksort_midpoint(numbers, left, k);
}

// Quicksort function that uses the median of three numbers as the pivot
void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i >= k) {
        return; // If the left index i is greater than or equal to the right index k, stop the recursion
    }

    // Choose the pivot to be the median of the first, middle, and last elements of the array
    int pivotIndex = i + (k - i) / 2;
    int pivotArray[3] = {numbers[i], numbers[pivotIndex], numbers[k]};
    sort(pivotArray, pivotArray + 3); // Sort the pivot array
    int pivot = pivotArray[1]; // The pivot is the median of the pivot array

    // Update the pivot index based on the chosen pivot
    if (pivot == numbers[i]) {
        pivotIndex = i;
    }
    else if (pivot == numbers[k]) {
        pivotIndex = k;
    }

    Swap(numbers, pivotIndex, i + (k - i) / 2); // Swap the pivot element with the midpoint

    // Partition the array
    int left = i;
    int right = k;

    // The rest of this function is the same as the Quicksort_midpoint function
    while (left <= right) {
        while (numbers[left] < pivot) {
            left++;
        }

        while (numbers[right] > pivot) {
            right--;
        }

        if (left <= right) {
            Swap(numbers, left, right);
            left++;
            right--;
        }
    }

    Quicksort_medianOfThree(numbers, i, right);
    Quicksort_medianOfThree(numbers, left, k);
}

// Function to sort an array using the insertion sort method
void InsertionSort(int numbers[], int numbersSize) {
    int i, key, j;

    // Loop over each element in the array
    for (i = 1; i < numbersSize; i++) {
        key = numbers[i]; // The element to be compared with the sorted part of the array
        j = i - 1; // The last element of the sorted part of the array

        // Move elements of the sorted part of the array that are greater than key
        // to one position ahead of their current position
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }

        numbers[j + 1] = key; // Insert the key into its correct position in the sorted part
    }
}

// Function to generate a random integer between low and high (inclusive)
int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

// Function to fill three arrays with the same random numbers
void fillArrays(int arr1[], int arr2[], int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE); // Generate a random number
        arr2[i] = arr1[i]; // Copy the number to the second array
        arr3[i] = arr1[i]; // Copy the number to the third array
    }
}

int main() {
    // Create three arrays
    int numbers1[NUMBERS_SIZE], numbers2[NUMBERS_SIZE], numbers3[NUMBERS_SIZE];

    // Fill the arrays with the same random numbers
    fillArrays(numbers1, numbers2, numbers3);

    clock_t Start, End;
    int elapsedTime;

    // Sort the first array using the Quicksort_midpoint function and measure the time taken
    Start = clock();
    Quicksort_midpoint(numbers1, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    printf("Time elapsed for Quicksort_midpoint: %d ms\n", elapsedTime);

    // Sort the second array using the Quicksort_medianOfThree function and measure the time taken
    Start = clock();
    Quicksort_medianOfThree(numbers2, 0, NUMBERS_SIZE - 1);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    printf("Time elapsed for Quicksort_medianOfThree: %d ms\n", elapsedTime);

    // Sort the third array using the InsertionSort function and measure the time taken
    Start = clock();
    InsertionSort(numbers3, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start) / CLOCKS_PER_MS;
    printf("Time elapsed for InsertionSort: %d ms\n", elapsedTime);

    return 0;
}
