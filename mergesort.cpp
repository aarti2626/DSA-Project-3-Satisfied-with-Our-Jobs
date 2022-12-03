#include<iostream>
#include<algorithm>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


void print(vector<int> arr, int size);
void mergeSort(vector<int>& arr, int l, int r);
void merge(vector<int>& arr, int p, int q, int r);

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr(n + 1);
    cout << "Enter elements separated by spaces:" << endl;
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Before Sorting: ";
    print(arr, n);

    //start clock
    auto start = steady_clock::now();

    mergeSort(arr, 0, n - 1);

    //stop clock
    auto stop = steady_clock::now();

    //calculate duration time of function
    auto duration = duration_cast<nanoseconds>(stop - start);

    cout << "After Sorting: ";
    print(arr, n);

    cout << "Sort completed in: " << duration.count() << " nanoseconds" << endl;
}

void merge(vector<int>& arr, int p, int q, int r) {
    //create two subarrays
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<int> L(n1);
    vector<int> M(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];

    //keep track of index of each subarray and merged array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    //until reach end of either subarray, put smaller element in merged array
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    //if reach the end of either subarray, add all remaining elements to merged array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    //recursively divides array into two subarrays, sorts and merges them
    if (l < r) {
        //find midpoint
        int m = l + (r - l) / 2;

        //sort each subarray
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        //merge the two subarrays
        merge(arr, l, m, r);
    }
}

void print(vector<int> arr, int size) {
    //print array
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}