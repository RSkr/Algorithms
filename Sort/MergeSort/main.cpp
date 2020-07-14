#include <iostream>
#include <omp.h>
using namespace std;

double omp_get_wtime( void );
void merge(int start, int middle, int end, int* arrayToSort, int* arrayToWork){
    int i = start, j, l;
    for(i; i <= end; i++){
        arrayToWork[i] = arrayToSort[i];
    }
    i = start;
    j = middle + 1;
    l = start;
    while(i <= middle && j <= end){
        if(arrayToWork[i] < arrayToWork[j])
            arrayToSort[l++] = arrayToWork[i++];
        else
            arrayToSort[l++] = arrayToWork[j++];

    }
    while(i <= middle) arrayToSort[l++] = arrayToWork[i++];
    while(j <= end) arrayToSort[l++] = arrayToWork[j++];
}

void mergesortNormal(int start, int end, int* arrayToSort, int* arrayToWork){
    int middle;
    if(start < end){
        middle = (start + end)/ 2;
        mergesortNormal(start, middle, arrayToSort, arrayToWork);
        mergesortNormal(middle + 1, end, arrayToSort, arrayToWork);
        merge(start, middle, end, arrayToSort, arrayToWork);
    }
}

void mergesortParallel(int start, int end, int* arrayToSort, int* arrayToWork){
    int middle;
    if(start < end){
        middle = (start + end)/ 2;
        if(end - start < 100){
            mergesortNormal(start, end, arrayToSort,arrayToWork);
            return;
        }

        #pragma omp task
        mergesortParallel(start, middle, arrayToSort, arrayToWork);

        #pragma omp task
        mergesortParallel(middle + 1, end, arrayToSort, arrayToWork);

        #pragma omp taskwait
        merge(start, middle, end, arrayToSort, arrayToWork);
    }
}

void printSortedArray(int* array, int n){
    for(int i = 0; i < n; i++){
        cout << array[i] << " ";
    }
}


void testcase(){
    int n;
    cin >> n;
    double start, stop;

    int arrayToSortNormal[n], arrayToSortParallel[n], arrayToWork[n];

    for(int i = 0; i < n; i++){
        cin >> arrayToSortNormal[i];
        arrayToSortParallel[i] = arrayToSortNormal[i];
    }

    start = omp_get_wtime();
    mergesortNormal(0, n - 1, arrayToSortNormal, arrayToWork);
    stop = omp_get_wtime();

    //printSortedArray(arrayToSortNormal, n);
    printf("\nTime normal: %g\n",stop-start);

    start = omp_get_wtime();
    mergesortParallel(0, n - 1, arrayToSortParallel, arrayToWork);
    stop = omp_get_wtime();

    //printSortedArray(arrayToSortParallel, n);
    printf("\nTime parallel: %g\n",stop-start);
}

int main() {
    testcase();
    return 0;
}