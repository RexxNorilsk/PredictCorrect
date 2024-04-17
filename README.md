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
Example results: <br/>
![image_2024-04-17_16-52-46](https://github.com/RexxNorilsk/PredictCorrect/assets/36097392/6e7c9ec6-d92f-4158-9d28-cf9ab7d23b62)
