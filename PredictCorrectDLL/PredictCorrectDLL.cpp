#include "pch.h" 
#include <utility>
#include <limits.h>
#include <iostream>
#include "PredictCorrectDLL.h"
#include "omp.h"
#include "mpi.h"
#include <string> 


using namespace std;
using F = double(*)(int, double*);


PREDICTCORRECTDLL_API double* Ñonsistently(
	double(*f)(int, double*), 
	int stepsCount, 
    double startArg,
	double* startValues, 
	double step,
	int countValues)
{

    double* values = new double[countValues];
    for (int i = 0; i < countValues; i++)
        values[i] = startValues[i];
    
    double* Predict = new double[countValues];
    double* Correct = new double[countValues];
    double* args = new double[countValues];
    double* argsPredict = new double[countValues];
    int j;
    for (double i = 0; i < stepsCount; i++, startArg += step)
    {
        args[0] = startArg;
        argsPredict[0] = startArg;
        for (j = 0; j < countValues; j++)
        {
            args[j + 1] = values[j];
        }
        for (j = 0; j < countValues; j++)
        {
            Predict[j] = values[j] + step * f(j, args);
        }

        for (j = 0; j < countValues; j++)
        {
            argsPredict[j + 1] = Predict[j];
        }

        for (j = 0; j < countValues; j++)
        {
            Correct[j] = values[j] + 0.5 * step * (f(j, args) + f(j, argsPredict));
        }

        for (j = 0; j < countValues; j++)
        {
            values[j] = Correct[j];
        }
    }
    delete Predict, Correct, args, argsPredict;

    return values;
}

PREDICTCORRECTDLL_API double* Omp(
    double(*f)(int, double*),
    int stepsCount,
    double startArg,
    double* startValues,
    double step,
    int countValues)
{
    double* Predict = new double[countValues];
    double* Correct = new double[countValues];
    double* args = new double[countValues];
    double* argsPredict = new double[countValues];
    int j;
    for (double i = 0; i < stepsCount; i++, startArg += step)
    {
        args[0] = startArg;
        argsPredict[0] = startArg;
        #pragma omp parallel for
        for (j = 0; j < countValues; j++)
        {
            args[j + 1] = startValues[j];
        }
        #pragma omp parallel for
        for (j = 0; j < countValues; j++)
        {
            Predict[j] = startValues[j] + step * f(j, args);
        }
        #pragma omp parallel for
        for (j = 0; j < countValues; j++)
        {
            argsPredict[j + 1] = Predict[j];
        }
        #pragma omp parallel for
        for (j = 0; j < countValues; j++)
        {
            Correct[j] = startValues[j] + 0.5 * step * (f(j, args) + f(j, argsPredict));
        }
        #pragma omp parallel for
        for (j = 0; j < countValues; j++)
        {
            startValues[j] = Correct[j];
        }
    }

    return startValues;
}



PREDICTCORRECTDLL_API double* MPI(
    double(*f)(int, double*),
    int stepsCount,
    double startArg,
    double* startValues,
    double step,
    int countValues) {
    
    MPI_Comm parentcomm, intercomm;
    MPI_Status status;
    MPI_Init(NULL, NULL);

    MPI_Comm_spawn(
        "PredictCorrectMPI",
        MPI_ARGV_NULL,
        2,
        MPI_INFO_NULL,
        0,
        MPI_COMM_WORLD,
        &intercomm,
        MPI_ERRCODES_IGNORE);

    int i, j;
    double
        y[2] = { 2.0, 1.0 },
        yy[2] = { 0.0, 0.0 },
        ff,
        ff_prog,
        time = 0.0,
        tau = 0.01,
        tmax = 1.0;

    int msgtag = 1;
    double tmp = 0.0;



    do {
        for (j = 0; j < 2; j++) {
            for (i = 0; i < 2; i++) {
                MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, msgtag, intercomm, &status);
                yy[status.MPI_SOURCE] = tmp;
            }

            for (i = 0; i < 2; i++) {
                MPI_Send(yy, 2, MPI_DOUBLE, i, msgtag, intercomm);
            }
        }
        time += tau;
    } while (time <= tmax);


    for (i = 0; i < 2; i++) {
        MPI_Recv(&tmp, 1, MPI_DOUBLE, MPI_ANY_SOURCE, msgtag, intercomm, &status);
        y[status.MPI_SOURCE] = tmp;
    }


    MPI_Finalize();
    return y;
}