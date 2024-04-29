#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

void mergesort(vector<int>& arr, int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;
        mergesort(arr, i, mid);
        mergesort(arr, mid + 1, j);
        inplace_merge(arr.begin() + i, arr.begin() + mid + 1, arr.begin() + j + 1);
    }
}

void parallel_mergesort(vector<int>& arr, int i, int j) {
    if (i < j) {
        if ((j - i) > 1000) {
            int mid = (i + j) / 2;
            #pragma omp task
            parallel_mergesort(arr, i, mid);
            #pragma omp task
            parallel_mergesort(arr, mid + 1, j);
            #pragma omp taskwait
            inplace_merge(arr.begin() + i, arr.begin() + mid + 1, arr.begin() + j + 1);
        } else {
            sort(arr.begin() + i, arr.begin() + j + 1);
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);

    // Initialize array with values
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Sequential sorting
    auto start_seq = chrono::high_resolution_clock::now();
    mergesort(arr, 0, n - 1);
    auto end_seq = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_seq = end_seq - start_seq;
    cout << "Sequential Merge sort: " << elapsed_seq.count() << "ms\n";
    cout << "Sorted array (sequential): ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Parallel sorting
    auto start_par = chrono::high_resolution_clock::now();
    #pragma omp parallel
    {
        #pragma omp single
        parallel_mergesort(arr, 0, n - 1);
    }
    auto end_par = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_par = end_par - start_par;
    cout << "Parallel Merge sort: " << elapsed_par.count() << "ms\n";
    cout << "Sorted array (parallel): ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
