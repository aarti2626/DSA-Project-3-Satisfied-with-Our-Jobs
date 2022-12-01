#include<iostream>
#include<algorithm>
#include <vector>
using namespace std;

void print(vector<int>& arr, int size);
int getMax(vector<int>& arr, int size);
void countSort(vector<int>& arr, int size);

int main() {
   int n;
   cout << "Enter the number of elements: ";
   cin >> n;
   vector<int> arr(n +1);
   cout << "Enter elements separated by spaces:" << endl;
   for(int i = 1; i<=n; i++) {
      cin >> arr[i];
   }
   cout << "Before Sorting: ";
   print(arr, n);
   countSort(arr, n);
   cout << "After Sorting: ";
   print(arr, n);
}



void print(vector<int>& arr, int size) { // prints values of an array 
   for(int i = 1; i<=size; i++)
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