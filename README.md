This software package is used to solve a system of differential equations using the predictor-corrector method. The complex is implemented and packaged in a DLL.  The solution method includes 3 steps: 
- Sequential calculations
- Calculations using OpenMP
- Calculations using MPI*

*If you need to use MPI in your calculations, it should write a dll
the library with the functions used and call it UserFunctions, as well as run
your program via mpiexec -n [number of threads]. Example of this library:

```
#include "pch.h"
#include "UserFunctions.h"
using namespace std;
USERFUNCTIONS_API double func(int id, double* args)
  {
  switch (id)
  {
  case 0:
  return sin(args[0] + args[1] * args[2]);
  case 1:
  return cos(args[0] * args[0] - args[1] + args[2]);
  }
}
```
