
#include <stdio.h>

#define getName(var)  #var

#define J "Jasmin (J)"
  
int main()
{
    printf("%s\n", getName(J));
    return 0;
} 