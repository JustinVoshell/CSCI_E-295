/* Seven functions with function arguments */
int f(int g(void));
void f(void g(void));
void f(int g(int x));
int *f(int *g( int *y ));
int***f(int***g( int **y));
void f(int* x, int* y, int* g(void));
int g(int*(*(f(void))));

/* Two function pointers */
int f(int (* g(void)));
int f(int **x, int **(***(g(void))));

/* Six illegal voids */
void f(int x, void y);
void f(void x);
void f(void ((x)));
void f(void *x);
void f(void, int *y);
void f(void, void);