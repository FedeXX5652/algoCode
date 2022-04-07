#include <stdio.h>

int main(){
    float num;
    char term;
    if(scanf("%f%c", &num, &term) != 2 || term != '\n')
        printf("failure\n");
    else
        printf("valid float followed by enter key: %f\n", num);
    return 0;
}
