#include <stdio.h>
#include <ctype.h>

char qst_1(){
    char n;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    do
    {
        printf("Ingrese el cartacter correspondiente a la respuesta elegida:\n");
        printf("1. Trineo (T)\n");
        printf("2. Nave (N)\n");
        printf("3. Camion (C)\n");
        printf("4. Alfombra (A)\n");
        scanf("%c", &n);
    } while (n != 't' || n != 'T' || n != 'n' || n != 'N' || n != 'c' || n != 'C' || n != 'a' || n != 'A');
    return tolower(n);
}


char qst_2(){
    char n;
    int flag = 0;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    do
    {
        if(flag == 0){
            printf("Ingrese el cartacter correspondiente a la respuesta elegida:\n");
            printf("1. Bolas de nieve (B)\n");
            printf("2. Pium pium (P)\n");
            printf("3. Kuchau (K)\n");
            printf("4. Genio (G)\n");
        }
        else{
            printf("Ingrese una respuesta valida:\n");
        }

        scanf("%c", &n);
        flag = 1;
    } while (n != 'b' || n != 'B' || n != 'p' || n != 'P' || n != 'k' || n != 'K' || n != 'g' || n != 'G');
    return tolower(n);
}


float qst_3(){
    float n;
    int flag = 0;
    float integer;
    float decimal;
    printf("--------------------------------------------------------------------------------------------\n");
    printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    do
    {
        if(flag == 0){
            printf("Ingrese la hora en forma decimal:\n");
        }
        
        scanf("%f", &n);
        float integer = (int) n;
        float decimal = n-integer;
        printf("integer: %f\n", integer);
        printf("decimal: %f\n", decimal);
    } while (integer <= 23 && decimal <= 59 && decimal >= 0 && integer >= 0);
    return n;
}


int main(){
    char ans_1;
    char ans_2;
    float ans_3;
    //char ans_4 = qst_4();

    ans_1 = qst_1();
    ans_2 = qst_2();
    ans_3 = qst_3();

    printf("ans_1: %c\n", ans_1);
    printf("ans_2: %c\n", ans_2);
    printf("ans_3: %f\n", ans_3);
}