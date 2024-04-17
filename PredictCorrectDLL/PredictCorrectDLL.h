// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef PREDICTCORRECTDLL_EXPORTS
#define PREDICTCORRECTDLL_API __declspec(dllexport)
#else
#define PREDICTCORRECTDLL_API __declspec(dllimport)
#endif

extern "C" PREDICTCORRECTDLL_API double* Ñonsistently(
	double(*f)(int, double*),
	int stepsCount,
	double startArg,
	double* startValues,
	double step,
	int countValues);

extern "C" PREDICTCORRECTDLL_API double* Omp(
	double(*f)(int, double*),
	int stepsCount,
	double startArg,
	double* startValues,
	double step,
	int countValues);

extern "C" PREDICTCORRECTDLL_API double* MPI(
	double(*f)(int, double*),
	int stepsCount,
	double startArg,
	double* startValues,
	double step,
	int countValues);

