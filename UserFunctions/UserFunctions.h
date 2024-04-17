// MathLibrary.h - Contains declarations of math functions
#pragma once

#ifdef USERFUNCTIONS_EXPORTS
#define USERFUNCTIONS_API __declspec(dllexport)
#else
#define USERFUNCTIONS_API __declspec(dllimport)
#endif

extern "C" USERFUNCTIONS_API double func(
	int id, 
	double* args
);


