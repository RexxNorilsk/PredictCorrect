#include <iostream>
#include <fstream>
#include "PredictCorrectDLL.h"

using namespace std;

double func(int id, double* args) {
    switch (id)
    {
        case 0:
            return sin(args[0] + args[1] * args[2]);
        case 1:
            return cos(args[0] * args[0] - args[1] + args[2]);
    }
}

void printArr(double *arr, int size) {
    for (int i = 0; i < size; i++)
    {
        cout << "\t" << arr[i] << endl;
    }
}

int main()
{
    double* startValues = new double[2]{ 2.0, 1.0 };
    cout << "Consistently:" << endl;
    clock_t tStart = clock();
    printArr(Сonsistently(func, 100, 0, startValues, 0.01, 2), 2);
    printf("    Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    cout << "OMP:" << endl;
    tStart = clock();
    printArr(Omp(func, 100, 0, startValues, 0.01, 2), 2);
    printf("    Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    cout << "MPI:" << endl;
    tStart = clock();
    printArr(MPI(func, 1000, 0, startValues, 0.01, 2), 2);
    printf("    Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    cout << "CUDA:" << endl;
}