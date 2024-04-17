#include <iostream>
#include "mpi.h"
#include "windows.h"


using namespace std;
using F = double(*)(int, double*);
#define n 2

int main(int argc, char** argv) {
    int size, rank;

    HINSTANCE hDLL;
    F func;
    hDLL = LoadLibrary(L"UserFunctions");
    func = (F)GetProcAddress(hDLL, "func");

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) { return 1; }
    MPI_Status state;
    MPI_Comm intercom;
    MPI_Comm_get_parent(&intercom);
    if (MPI_Comm_size(intercom, &size) != MPI_SUCCESS) { MPI_Finalize(); return 2; }
    if (MPI_Comm_rank(intercom, &rank) != MPI_SUCCESS) { MPI_Finalize(); return 3; }
    MPI_Status status;
    double
        y[n] = { 2.0, 1.0 },
        yy[n] = { 0.0, 0.0 },
        Predict,
        Correct,
        time = 0.0,
        tau = 0.01,
        tmax = 1.0;


    int msgtag = 1;
    int i, j;

    do {
        Predict = func(rank, y);

        yy[rank] = y[rank] + tau * func(rank, y);
        MPI_Send(&yy[rank], 1, MPI_DOUBLE, 0, msgtag, intercom);
        MPI_Recv(&yy, n, MPI_DOUBLE, 0, msgtag, intercom, &status);

        Correct = func(rank, yy);

        y[rank] = y[rank] + tau * 0.5 * (Predict + Correct);

        MPI_Send(&y[rank], 1, MPI_DOUBLE, 0, msgtag, intercom);
        MPI_Recv(&y, n, MPI_DOUBLE, 0, msgtag, intercom, &status);
        time += tau;
    } while (time <= tmax);
    
    MPI_Send(&y[rank], 1, MPI_DOUBLE, 0, msgtag, intercom);

    MPI_Finalize();
    FreeLibrary(hDLL);
    return 0;
}