#include <iostream>
#include <omp.h>

using namespace std;

// function to generate an array of random integers
void generateArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }
}

// function to perform parallel reduction to find the minimum value
int parallelMin(int arr[], int n) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// function to perform parallel reduction to find the maximum value
int parallelMax(int arr[], int n) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

// function to perform parallel reduction to find the sum of values
int parallelSum(int arr[], int n) {
    int sum_val = 0;
    #pragma omp parallel for reduction(+:sum_val)
    for (int i = 0; i < n; i++) {
        sum_val += arr[i];
    }
    return sum_val;
}

// function to perform parallel reduction to find the average value
double parallelAverage(int arr[], int n) {
    double sum_val = 0.0;
    #pragma omp parallel for reduction(+:sum_val)
    for (int i = 0; i < n; i++) {
        sum_val += arr[i];
    }
    return sum_val / n;
}

int main() {
    int n = 100;
    int arr[n];
    generateArray(arr, n);
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";
    cout << "Minimum value: " << parallelMin(arr, n) << endl;
    cout << "Maximum value: " << parallelMax(arr, n) << endl;
    cout << "Sum of values: " << parallelSum(arr, n) << endl;
    cout << "Average value: " << parallelAverage(arr, n) << endl;
    return 0;
}
