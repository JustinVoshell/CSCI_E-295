/* 2 no pointers to void */
void *i;                 
void (*f(int x));        

/* 2 no pointers to functions */
int (*pf)(void);
int (*x[])(void);

/* 4 no arrays of functions */
int x[](void);
int (x[])(void);
int ((*x)[])(void);
int (((*x)[])(void);

/* 2 no functions returning arrays */
int f(void)[];
int (f(void))[];

/* 4 only first dimension may be missing from abstractly declarated array */
int f(int [][]);
int f(int ([])[]);
int f(int *([])[]);
int f(int (*[3])(([])[]));

