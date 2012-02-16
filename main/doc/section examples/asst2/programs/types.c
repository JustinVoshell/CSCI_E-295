int a;
short b;
short int c;
signed short d;

signed short int e;
signed int f;
signed int g;
long h;
long int i;

signed long j;
signed long int k;
unsigned short int l;

unsigned short m;

unsigned long int o;
unsigned long int p;
char q;
signed char r;
unsigned char s;


int funcDeclar(int crap, int crap1); 
int printf(char *c, int i)
{
  int a, b;
  funcDeclar(a, b);
  return 1;
}


int func( int x )
{
    return 0;
}

int main( int p1, char p2 )
{
    unsigned short int s1_test1, s1_test2;
    int s1_a;
    unsigned short int s1_b;
    int *p_s1_array1[16];
    char s1_array2[16];
    {
        int p1;
        short int s2_test1, s2_test2;
        int s2_a;
        int s3_a;
        char s2_b;
        s2_a = 0;
        s2_b = 0;
        while(1)
	  {
            char* p_s3_a;
            s2_a++;
            s2_b++;
            {
                int* p_s4_a;
                {
                    int s5_a;
                }
                {
                    int s5_a;
                }
            }
            break;
	  }

	{ 
	  char* p_s3_a;
	  int s3_a;
	  char s3_b;
            for( ; ; )
	      {
                unsigned char s4_a;
                int *p_s4_b, s4_c;
                s4_a = 0;
                s4_a++;
                s4_a = 5;
                {
                    int s5_a;
                }
                break;
	      }
            
            for( s3_a = 0; s3_a < 5; s3_a ++ )
	      {
                printf("%d, for loop\n", s3_a);
	      }
        }
    }
}

char foo_global;
int foo( int foo_p1, int foo_p2 )
{
    int foo_a;
    int foo_b;
    int x;
    x=1;
    do
      {
        x = 5;
      } while(0);
    return x;
    func(x);
}

void void_foo( void )
{
    int foo_a;
    int foo_b;
    int x;
    foo_a = 0;
    foo_b = 1;
    x = 8;
    if( foo_a < foo_b )
      {
      }
    
    func(x);
}

void void_foo_2()
{
    int foo_a;
    int foo_b;
    int x;
    foo_a = 0;
    foo_b = 1;
    x = 8;
    if( foo_a < foo_b )
      {
      }
    else
      {
        int x;
      }
    func(x);
}

void_foo_3()
{
    int foo_a;
    int foo_b;
    int x;
    x = 5;
    func(x);
    return 0;
}

short* p_void_foo_4()
{
    int foo_a;
    int foo_b;
    int x;
    x = 5;
    func(x);
    return(0);
}

short* p_void_foo_5( int* foo_p1 )
{
    int foo_a;
    int foo_b;
    int x;
    short* pX;
    pX = 0;
    x = 5;
    func(x);
    return pX;
}

void voidFunction()
{

}

int funcDeclar(int a, int b)
{
   return a + b;
}

