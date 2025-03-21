#include <iostream>
#include <chrono>
#include "sampler.h"

using namespace std;
using namespace std::chrono;

const int32_t 
    N_ITEMS = 10000000,
    THRESHOLD = 30;

int32_t 
    data1[N_ITEMS],
    data2[N_ITEMS],
    aux[N_ITEMS];

void mergeSort(int32_t *data,int32_t low,int32_t high) { // NOLINT(*-no-recursion)
    int32_t 
        L = low,
        mid = (low + high) / 2,
        R = mid + 1,
        k = low;
    
    if (low < high) {
        mergeSort(data,low,mid);
        mergeSort(data,mid+1,high);
        
        while (L <= mid && R <= high)
            if (data[R] < data[L])
                aux[k++] = data[R++];
            else
                aux[k++] = data[L++];
            
        while (L <= mid)
            aux[k++] = data[L++];
        
        while (R <= high)
            aux[k++] = data[R++];
        
        for (k=low;k<=high;k++)
            data[k] = aux[k];
    }
}

void hybridSort(int32_t *data,int32_t low,int32_t high) { // NOLINT(*-no-recursion)
    int32_t
        L = low,
        mid = (low + high) / 2,
        R = mid + 1,
        k = low;

    if (high - low > THRESHOLD) {
        hybridSort(data,low,mid);
        hybridSort(data,mid+1,high);

        while (L <= mid && R <= high)
            if (data[R] < data[L])
                aux[k++] = data[R++];
            else
                aux[k++] = data[L++];

        while (L <= mid)
            aux[k++] = data[L++];

        while (R <= high)
            aux[k++] = data[R++];

        for (k=low;k<=high;k++)
            data[k] = aux[k];
    } else {
        int32_t 
            tmp,
            i,j;
        for (i=low+1;i<=high;i++) {
            tmp = data[i];
            for (j=i-1;j>=low && data[j] > tmp;j--)
                data[j+1] = data[j];
            data[j+1] = tmp;
        }
    }
}

void sort1(int32_t *data,int32_t n) {
    mergeSort(data,0,n-1);
}

void sort2(int32_t *data,int32_t n) {
    hybridSort(data,0,n-1);
}

int main() {
    Sampler
        s(N_ITEMS);
    
    for (int32_t i=0;i<N_ITEMS;i++)
        data1[i] = data2[i] = s.getSample();
    
    auto
        start = high_resolution_clock::now();
    
    sort1(data1,N_ITEMS);
    
    auto
        end = high_resolution_clock::now();
    
    auto
        time1 = duration_cast<microseconds>(end-start);
    
    start = high_resolution_clock::now();
    
    sort2(data2,N_ITEMS);
    
    end = high_resolution_clock::now();
    
    auto
        time2 = duration_cast<microseconds>(end-start);
    
    cout << " Time for merge sort: " << time1.count() << "us" << endl;
    cout << "Time for hybrid sort: " << time2.count() << "us" << endl;

    double
        diff = (double)(time1.count() - time2.count()) * 100.0 / (double)(time1.count());

    cout << "Relative improvement: " << diff << '%' << endl;

    for (uint32_t i=0;i<N_ITEMS;i++) {
        if (data1[i] != data2[i])
            throw runtime_error("main: lists are different");
        if (i > 0 && data1[i] < data2[i-1])
            throw runtime_error("main: data not sorted");
    }

    return 0;
}
