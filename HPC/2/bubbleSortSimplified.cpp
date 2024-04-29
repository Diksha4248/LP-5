#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

void sequential_bubble_sort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void parallel_bubble_sort(vector<int>& arr) {
    int n = arr.size();
    #pragma omp parallel for shared(arr)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int n;
    cin>>n;
    vector<int> arr(n);

    // Initialize array with values
    for (int i = 0; i < n; ++i) {
        cin>>arr[i];
    }

    // Sequential sorting
    auto start_seq = high_resolution_clock::now();
    sequential_bubble_sort(arr);
    auto end_seq = high_resolution_clock::now();
    duration<double,milli> elapsed_seq = end_seq - start_seq;
    cout << "Sequential Bubble sort: " << elapsed_seq.count() << "ms\n";
    cout << "Sorted array (sequential): ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Parallel sorting
    auto start_par = high_resolution_clock::now();
    parallel_bubble_sort(arr);
    auto end_par = high_resolution_clock::now();
    duration<double, milli> elapsed_par = end_par - start_par;
    cout << "Parallel Bubble sort: " << elapsed_par.count() << "ms\n";
    cout << "Sorted array (parallel): ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
