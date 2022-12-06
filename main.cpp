#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <chrono>
#include <fstream>
#include <sstream>
#include <locale>
using namespace std;
using namespace std::chrono;


vector<vector<string>> readCSV(string filepath);
void execute(int n, int sort, vector<vector<string>>& csv);
void merge(vector<vector<string>> &csv, int sort_index, int p, int q, int r);
void mergeSort(vector<vector<string>>& csv, int sort_index, int l, int r);
int getMax(vector<vector<string>>& csv, int sort_index, int size);
void countSort(vector<vector<string>>& csv, int sort_index, int size);
void print(vector<vector<string>> csv);
void findCompany(vector<vector<string>> csv, string company);

int main() {

    //read in data from csv
    cout << "\nReading File... 100,000 lines could take a little bit of time :)" << endl;
    vector<vector<string>> csv = readCSV("out.csv");

    bool running = true;

    //repeat prompt until user wants to end
    while (running) {

        //choose which attribute to sort by
        int n = 0;
        while (n < 1 || n > 8) {
            // these numbers will be the index that gets sorted in the 2D array
            cout << "\nPlease select what you would like to sort by: " << endl;
            cout << "[1]: Overall Rating" << endl <<
                "[2]: Work Life Balance" << endl <<
                "[3]: Culture Values" << endl <<
                "[4]: Diversity Factor" << endl <<
                "[5]: Career Opportunities" << endl <<
                "[6]: Comp Benefits" << endl <<
                "[7]: Senior Management" << endl <<
                "[8]: END" << endl;

            cin >> n;
        }

        //end program if user wants to end
        if (n == 8)
            break;

        map<int, string> columns{ {1, "Overall Rating"}, {2, "Work Life Balance"}, {3, "Culture Values"}, {4, "Diversity Factor"}, {5, "Career Opportunities"}, {6, "Comp Benefits"}, {7, "Senior Management"}};

        n += 3;

        cout << "\n\n";

        //print 2d vector before sorting
        cout << "\nBefore Sorting by " << columns[n - 3] << "(Column #" << n + 1 << "): " << endl;
        print(csv);

        //choose which sorting algorithm to use
        int sort = 0;
        while (sort < 1 || sort > 3) {
            cout << "\nHow would you like to sort? Enter 1 or 2: " << endl;
            cout << "[1]: Merge Sort" << endl << "[2]: Counting Sort" << endl << "[3]: Let's Compare Both" << endl;
            cin >> sort;
        }
        
        cout << "\n\n\n\n\n\n";
        execute(n, sort, csv); 
        
        //print sorted 2d vector
        cout << "\nAfter Sorting by " << columns[n - 3] << " (Column #" << n + 1 << "): " << endl;
        print(csv);

        //choose which company to subset reviews for, repeat until user wants to go back
        while (running) {
            cout << "\nChoose company or BACK: ";
            string company;
            cin >> company;
            if (company == "BACK" || company == "back")
                break;
            subsetCompany(csv, company);
        }

        
    }
    return 0;
}

vector<vector<string>> readCSV(string filepath) {
    //read csv data into vector
    vector<vector<string>> csv;
    vector<string> row;
    string line, cell;

    fstream file(filepath, ios::in);
    if (file.is_open()) {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);
            
            bool ignore_first = true;
            while (getline(str, cell, ',')) {
                if (ignore_first) {
                    ignore_first = false;
                    continue;
                }
                else {
                    row.push_back(cell);
                }
            }
                
            csv.push_back(row);
        }
    } else {
        cout << "Could not open the file\n";
    }

    return csv;
}

string AddCommas(int time) {
    //add commas to long numbers
    stringstream ss;
    ss.imbue(locale(""));
    ss << fixed << time;
    return ss.str();
}

void execute(int n, int sort, vector<vector<string>> &csv) {
    if (sort == 1) {    //mergesort

        vector<vector<string>> mergesort_csv = csv;

        // remove line defining column titles
        mergesort_csv.erase(mergesort_csv.begin());
        
        cout << "Performing Merge Sort..." << endl;

        // timer start
        auto start = steady_clock::now();

        // execute merge sort
        mergeSort(mergesort_csv, n, 0, mergesort_csv.size() - 1);

        // timer stop
        auto stop = steady_clock::now();

        // report total time taken for sort
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Merge Sort completed in: " << AddCommas(duration.count()) << " nanoseconds" << endl;

        //insert columns titles at beginning of sorted vector
        mergesort_csv.insert(mergesort_csv.begin(), csv[0]);
        csv = mergesort_csv;

    } else if (sort == 2) {     //counting sort

        vector<vector<string>> countsort_csv = csv;

        // remove line defining column titles
        countsort_csv.erase(countsort_csv.begin());

        cout << "Performing Counting Sort..." << endl;

        // timer start
        auto start2 = steady_clock::now();

        //execute counting sort
        countSort(countsort_csv, n, countsort_csv.size());

        // timer stop
        auto stop2 = steady_clock::now();
        
        // report total time taken for sort
        auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
        cout << "Counting Sort completed in: " << AddCommas(duration2.count()) << " nanoseconds" << endl;

        //insert column titles at beginning of sorted vector
        countsort_csv.insert(countsort_csv.begin(), csv[0]);
        csv = countsort_csv;

    } else if (sort == 3) {     //perform both merge sort and counting sort

        vector<vector<string>> mergesort_csv = csv;

        //remove line defining column titles
        mergesort_csv.erase(mergesort_csv.begin());

        cout << "Performing Merge Sort..." << endl;

        auto start3 = steady_clock::now();

        mergeSort(mergesort_csv, n, 0, mergesort_csv.size() - 1);

        auto stop3 = steady_clock::now();

        //report total time taken for sort
        auto durationMerge = duration_cast<nanoseconds>(stop3 - start3);
        cout << "Merge Sort completed in: " << AddCommas(durationMerge.count()) << " nanoseconds" << endl;

        cout << endl;

        vector<vector<string>> countsort_csv = csv;

        //remove line defining column titles
        countsort_csv.erase(countsort_csv.begin());

        cout << "Performing Counting Sort..." << endl;

        auto start4 = steady_clock::now();

        countSort(countsort_csv, n, countsort_csv.size());
        
        auto stop4 = steady_clock::now();

        //report total time taken for sort
        auto durationCount = duration_cast<nanoseconds>(stop4 - start4);
        cout << "Counting Sort completed in: " << AddCommas(durationCount.count()) << " nanoseconds" << endl;

        countsort_csv.insert(countsort_csv.begin(), csv[0]);
        csv = countsort_csv;
    }

}


void merge(vector<vector<string>>& csv, int sort_index, int p, int q, int r) {
   
    //create two subarrays
    int n1 = q - p + 1;
    int n2 = r - q;

    vector<vector<string>> L(n1);
    vector<vector<string>> M(n2);

    for (int i = 0; i < n1; i++)
        L[i] = csv[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = csv[q + 1 + j];

    //keep track of index of each subarray and merged array
    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    //until reach end of either subarray, put smaller element in merged array
    while (i < n1 && j < n2) {
        if (stoi(L[i][sort_index]) <= stoi(M[j][sort_index])) {
            csv[k] = L[i];
            i++;
        }
        else {
            csv[k] = M[j];
            j++;
        }
        k++;
    }

    //if reach the end of either subarray, add all remaining elements to merged array
    while (i < n1) {
        csv[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        csv[k] = M[j];
        j++;
        k++;
    }
}

void mergeSort(vector<vector<string>> &csv, int sort_index, int l, int r) {
    //recursively divides array into two subarrays, sorts and merges them
    if (l >= r) {
        return;
    } else {
        //find midpoint
        int m = l + (r - l) / 2;

        //sort each subarray
        mergeSort(csv, sort_index, l, m);
        mergeSort(csv, sort_index, m + 1, r);

        //merge the two subarrays
        merge(csv, sort_index, l, m, r);
    }
}

int getMax(vector<vector<string>>& csv, int sort_index, int size) { // returns max given the 2d vector, sorting criteria, number of rows
    int max = stoi(csv[0][sort_index]);
    for (int i = 1; i < size; i++) {
        if (stoi(csv[i][sort_index]) > max)
            max = stoi(csv[i][sort_index]);
    }
    return max;
}

void countSort(vector<vector<string>>& csv, int sort_index, int size) { // executes counting sort 

   // initialize output and count arrays
    vector<vector<string>> output(size);
    int max = getMax(csv, sort_index, size);
    vector<int> count(max + 1);

    // set initial values in count
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    // get frequencies of every val and update count 
    for (int i = 0; i < size; i++)
        count[stoi(csv[i][sort_index])]++;

    // start summing up count values
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    // now, copy over summed values to output vector 
    for (int i = size - 1; i >= 0; i--) {
        output[count[stoi(csv[i][sort_index])] - 1] = csv[i];
        count[stoi(csv[i][sort_index])] -= 1;
    }

    // copy over to main arr 
    for (int i = 0; i < size; i++) {
        csv[i] = output[i];
    }

}

void print(vector<vector<string>> csv) {
    //print column names and first and last 10 reviews in vector
    string line;
    for (int j = 0; j < csv[0].size(); j++) {
        line = line +  csv[0][j] + " | ";
    }
    cout << "\nColumns: " << endl;
    cout << line.substr(0, line.size() - 3) << endl;

    cout << "\nFirst 10 lines: \n" << endl;
    for (int i = 1; i < 11; i++) {
        string line;
        for (int j = 0; j < csv[i].size(); j++)
        {
            line = line + csv[i][j] + " | ";
        }
        cout << line.substr(0, line.size() - 3) << endl;
    }

    cout << "\nLast 10 lines: \n" << endl;
    for (int i = csv.size() - 10; i < csv.size(); i++) {
        string line;
        for (int j = 0; j < csv[i].size(); j++)
        {
            line = line + csv[i][j] + " | ";
        }
        cout << line.substr(0, line.size() - 3) << endl;
    }

    cout << endl;

}

void subsetCompany(vector<vector<string>> csv, string company) {
    //subset vector to only contain reviews for specified company
    vector<vector<string>> companyData;
    companyData.push_back(csv[0]);
    for (int i = 1; i < csv.size(); i++) {
        string line;
        if (csv[i][0] == company) {
            companyData.push_back(csv[i]);
        }
    }

    //if vector has no reviews, print no data for company
    if (companyData.size() == 1) {
        cout << "\nNo data on company" << endl;
    } else {
        print(companyData);
    }
}
