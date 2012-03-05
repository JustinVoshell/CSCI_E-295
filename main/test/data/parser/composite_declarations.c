/* 
  signed int i,
  pointer to signed int pi,
  function fpi returning pointer to signed int
*/
int i, *pi, *fpi(void);

/*
  function f, with parameter pointer to signed integer x, returning void
  function g, with parameter pointer to signed integer y, returning void
  function h with parameter void returning void
*/

void f(int *x), g(int *y), h(void);

/*
  array of three pointers to signed integers,
  pointer to array of three integers
*/
int *arrayOf3pToInt[3], (*pToArrayOf3int)[3];

/*
  function, with no parameters, returning pointer to array of signed integers
*/
int (*fReturningPtoIntArray(void))[];  

/*
  function f, with parameter array of signed integers, returning signed integer 
*/
int f(int[]);  

/*
  function f, returning void, with parameters:
    array of signed integers x,
    array of arrays of two signed integers y,
    pointer to an array of an array of signed integers,
    array of arrays of three signed integers
  
*/
void f(int x[], int[][2], int (*[])[], int ([])[3]);

/*
  function f, returning pointer to pointer to signed integer, with parameters:
    pointer to array of array of signed integers x
*/
int (**f(int(*x[])[]));
