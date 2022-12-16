#include <iostream>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

void merge(int* array, int const left, int const mid,
    int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;

    auto* leftArray = new int[subArrayOne],
        * rightArray = new int[subArrayTwo];

    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne
        = 0,
        indexOfSubArrayTwo
        = 0;
    int indexOfMergedArray
        = left;

    while (indexOfSubArrayOne < subArrayOne
        && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int* array, int const begin, int const end)
{
    if (begin >= end)
        return;

    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}


int main() {
    setlocale(LC_ALL, "Russian");
    srand(time(0));
    long long dur = 0;
    ofstream fout("MergeSortResults.txt");
    for (int k = 1; k <= 1000; k++) {
        int* arr = new int[10000000];
        for (int i = 0; i < 10000000; i++) {
            arr[i] = rand();
        }
        auto arr_size = 10000000;

        auto start = high_resolution_clock::now();

        mergeSort(arr, 0, arr_size - 1);

        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>(stop - start);

        dur += duration.count();

        fout << k << " попытка " << duration.count() << " микросекунд" << endl;
        cout << k << " попытка " << duration.count() << " микросекунд" << endl;

        delete[] arr;
    }

    fout << "Среднее значение " << dur / 1000;
    cout << "Среднее значение " << dur / 1000;

    return 0;
}