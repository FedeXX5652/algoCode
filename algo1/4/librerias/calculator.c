#include <stdio.h>
#include "calculator.h"

int add(int a, int b){
    return a + b;
}

int sub(int a, int b){
    return a - b;
}

int mul(int a, int b){
    return a * b;
}

int div(int a, int b){
    return a / b;
}

int pot(int a, int b){
    int i;
    int res = 1;
    for(i = 0; i < b; i++){
        res *= a;
    }
    return res;
}