// Copyright 2023 Polozov Vladislav

#include "task_3/polozov_v_double_radix_sort_simple_merge/double_radix_sort_simple_merge.h"

double fRand(double fMin, double fMax)
{
    std::random_device device;
    std::mt19937 generator(device());
    int f = (int)rand();
    return fMin + f * (fMax - fMin)/RAND_MAX;
}


void CountingSort(double* inp, double* tmp, int byteNum, int n){
    unsigned char * mas = (unsigned char*) inp;
    //mas содержит 8 * n элементов , мы одно число double разложили на 8 байт
    //и к этому применяем сортировку подсчетом
    std::vector<std::vector<int>>count(256);
    for(int i = 0;i<n;i++){
        count[mas[8 * i + byteNum]].push_back(i);
    }
    int cur = 0;
    for(int i = 0;i<256;i++){
        for(auto j : count[i]){
            tmp[cur] = inp[j];
            cur++;
        }
    }
}

void RadixSortDouble(double* inp , int n){

    double *tmp = new double[n];
    CountingSort(inp,tmp,0,n);
    CountingSort(tmp,inp,1,n);
    CountingSort(inp,tmp,2,n);
    CountingSort(tmp,inp,3,n);
    CountingSort(inp,tmp,4,n);
    CountingSort(tmp,inp,5,n);
    CountingSort(inp,tmp,6,n);
    CountingSort(tmp,inp,7,n);
    delete []tmp;
}

void getRandomInput(double* inp, int n, ){

    for(int i = 0;i<n;i++){
        inp[i] = fRand(1,100);
        cout<<inp[i]<<' ';
    }
    cout<<'\n';

}
