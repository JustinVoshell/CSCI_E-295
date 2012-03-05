/* Two illegal void declarations */
void x[];
int x[void];

/* Six invalid incomplete array declarations */
int x[][];
int x[][1][2][];
int x[1][];
int x[1][2][][3]; 
int ((x[]))[];
int x[](([]));
      
