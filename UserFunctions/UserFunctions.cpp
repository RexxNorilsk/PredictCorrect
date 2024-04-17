#include "pch.h" 
#include <utility>
#include <limits.h>
#include <iostream>
#include "UserFunctions.h"
#include "omp.h"
#include <string> 


using namespace std;


USERFUNCTIONS_API double func(
    int id, double* args)
{
    switch (id)
    {
    case 0:
        return sin(args[0] + args[1] * args[2]);
    case 1:
        return cos(args[0] * args[0] - args[1] + args[2]);
    }
}