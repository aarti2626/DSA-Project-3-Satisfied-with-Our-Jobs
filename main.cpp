#include<iostream>
#include<algorithm>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;


void print(vector<int> arr, int size);
void mergeSort(vector<int>& arr, int l, int r);
void merge(vector<int>& arr, int p, int q, int r);
int getMax(vector<int>& arr, int size);
void countSort(vector<int>& arr, int size);
void execute(int n, int sort);

int main() {

    // these numbers will be the index that gets sorted in the 2D array, make sure these line up
    cout << "Please select what you would like to sort by: " << endl;
    cout << "[1]: Overall rating" << endl <<
    "[2]: Work life balance" << endl <<
    "[3]: Culture values" << endl <<
    "[4]: Diversity factor" << endl <<
    "[5]: Career opportunities" << endl <<
    "[6]: Comp benefits" << endl << 
    "[7]: Senior Management" << endl;

    int n;
    cin >> n;

    cout << "Before Sorting: ";
    //print(arr, n); here, call print() on the correct column, maybe don't print all the values, just the first few and the last

    cout << "How would you like to sort? Enter 1 or 2: " << endl;
    cout << "[1]: Merge Sort" << endl << "[2]: Counting Sort" << endl << "[3]: Let's Compare Both" << endl;
    int sort;
    cin >> sort;
    execute(n, sort); // TODO: update this function so that the 2D vector is passed in 
    

    cout << "After Sorting: ";
    //print(arr, n); same as above: call print() on correct column, do not print all values 

    return 0;
}

void execute(int n, int sort){
    if(sort == 1){ // 
        auto start = steady_clock::now();
        // call merge sort on index n of the main vector 
        auto stop = steady_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Sort completed in: " << duration.count() << " nanoseconds" << endl;
    }else if(sort == 2){
        auto start2 = steady_clock::now();
        // call counting sort on index n of the main vector
        auto stop2 = steady_clock::now();
        auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
        cout << "Sort completed in: " << duration2.count() << " nanoseconds" << endl;
    }else if (sort == 3){
        auto start3 = steady_clock::now();
        // call merge sort and get time 
        auto stop3 = steady_clock::now();
        auto durationMerge = duration_cast<nanoseconds>(stop3 - start3);
        cout << "Sort completed in: " << durationMerge.count() << " nanoseconds" << endl;

        start3 = steady_clock::now();
        // call merge sort and get time 
        stop3 = steady_clock::now();
        auto durationCount = duration_cast<nanoseconds>(stop3 - start3);
        cout << "Sort completed in: " << durationCount.count() << " nanoseconds" << endl;
    }

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

int getMax(vector<int>& arr, int size) { // returns max given an arr and a size 
   int max = arr[1];
   for(int i = 2; i<=size; i++) {
      if(arr[i] > max)
         max = arr[i];
   }
   return max; 
}

void countSort(vector<int>& arr, int size) { // executes counting sort 

   // initialize output and count arrays
   vector<int> output(size + 1);
   int max = getMax(arr, size);
   vector<int> count(max + 1);
   
   // set initial values in count
   for(int i = 0; i<=max; i++)
      count[i] = 0;     

   // get frequencies of every val and update count 
   for(int i = 1; i <=size; i++)
      count[arr[i]]++;     

   // start summing up count values
   for(int i = 1; i<=max; i++)
      count[i] += count[i-1];     

   // now, copy over summed values to output vector 
   for(int i = size; i>=1; i--) {
      output[count[arr[i]]] = arr[i];
      count[arr[i]] -= 1; 
   }

   // copy over to main arr 
   for(int i = 1; i<=size; i++) {
      arr[i] = output[i]; 
   }
}