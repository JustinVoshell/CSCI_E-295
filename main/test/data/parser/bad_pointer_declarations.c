/* Five bad pointer declarations */

int x*;
*int x;
*(int x);
int ((x)*);
int (*(int y));
