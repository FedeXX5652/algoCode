#include <stdio.h>
#include <ctype.h>

#define J "Jasmin (J)"
#define R "Rayo McQueen (R)"
#define O "Olaf (O)"
#define S "Stitch (S)"

#define trineo 'T'
#define nave 'N'
#define camion 'C'
#define alfombra 'A'

#define bola_de_nieve 'B'
#define pium_pium 'P'
#define kuchau 'K'
#define genio  'G'

void qst_1(int* score){
    char ans;

    // Realizo la pregunta 1
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Trineo (T)\n");
    printf("2. Nave (N)\n");
    printf("3. Camion (C)\n");
    printf("4. Alfombra (A)\n\n");

    // Espero la respuesta
    scanf(" %c", &ans);
    ans = (char)toupper(ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(ans != trineo && ans != nave && ans != camion && ans != alfombra){
        printf("Ingrese una respuesta valida: ");
        scanf(" %c", &ans);
        ans = (char)toupper(ans);
    }

    // Asigno un score a la respuesta
    if(ans == trineo || ans == nave){
        *score = 10;
    }
    else if(ans == camion || ans == alfombra){
        *score = 20;
    }

    //printf("Socre from qst_1: %d\n", *score);
}


void qst_2(int* qst_score){
    char ans;

    // Realizo la pregunta 2
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Bolas de nieve (B)\n");
    printf("2. Pium pium (P)\n");
    printf("3. Kuchau (K)\n");
    printf("4. Genio (G)\n\n");

    // Espero la respuesta
    scanf(" %c", &ans);
    ans = (char)toupper(ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(ans != bola_de_nieve && ans != pium_pium && ans != kuchau && ans != genio){
        printf("Ingrese una respuesta valida: ");
        scanf(" %c", &ans);
        ans = (char)toupper(ans);
    }

    // Asigno un score a la respuesta
    if(ans == bola_de_nieve){
        (*qst_score) = 3;
    }
    else if(ans == pium_pium){
        (*qst_score) = 6;
    }
    else if(ans == kuchau){
        (*qst_score) = 9;
    }
    else if(ans == genio){
        (*qst_score) = 12;
    }

    //printf("Socre from qst_2: %d\n", (*qst_score));
}


/*

*/
void qst_3(int* qst_score){
    float hour_value;

    // Realizo la pregunta 3
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    printf("\nIngrese la hora en forma decimal: ");

    // Espero la respuesta
    scanf(" %f", &hour_value);
    int integer = (int)hour_value;
    int decimal = ((int)(hour_value-(float)integer))*10;

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(decimal < 0 || decimal > 59 || integer < 0 || integer > 23){
        printf("\nIngrese una hora valida: ");
        scanf(" %f", &hour_value);
        integer = (int)hour_value;
        decimal = ((int)(hour_value-(float)integer))*10;
    }

    // Asigno un score a la respuesta
    if(hour_value<=15.30){
        (*qst_score) = 0;     // 0 equivale a llegar temprano
    }
    else if(hour_value>15.30){
        (*qst_score) = 1;     // 1 equivale a llegar tarde
    }

    //printf("Socre from qst_3: %d\n", (*qst_score));
}


/*
    Precondicion:
        - Requiere que se le ingrese un valor del 1 al 10 en forma de entero
    Postcondicion:
        - Asigna un valor por referencia a la variable score alocada en el main
            + Si el valor ingresado es mayor o igual a 1 y menor o igual a 3, asigna un valor de 1 al score
            + Si el valor ingresado es mayor o igual a 4 y menor o igual a 6, asigna un valor de 2 al score
            + Si el valor ingresado es mayor o igual a 7 y menor o igual a 8, asigna un valor de 3 al score
            + Si el valor ingresado es mayor o igual a 9 y menor o igual a 10, asigna un valor de 4 al score
*/
void qst_4(int* qst_score){
    float exam_score = 0;       // PREGUNTAR XQ SE USA FLOAT EN EL EJEMPLO 2 AIUUUUUUUUUUUUUUDAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA AIUDA

    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte?\n");
    printf("Ingrese el valor de su nota en entero (1-10): ");

    // Espero la respuesta
    scanf(" %f", &exam_score);;

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(exam_score < 1 || exam_score > 10){
        printf("\nIngrese una nota valida: ");
        scanf(" %f", &exam_score);
    }

    if(exam_score >= 1 && exam_score <= 3){
        (*qst_score) = 1;
    }
    else if(exam_score >= 4 && exam_score <= 6){
        (*qst_score) = 2;
    }
    else if(exam_score >= 7 && exam_score <= 8){
        (*qst_score) = 3;
    }
    else if(exam_score >= 9 && exam_score <= 10){
        (*qst_score) = 4;
    }

    //printf("Socre from qst_4: %d\n", (*qst_score));
}


/*
    Pre condiciones:
        - El final_score debe tener un valor entre 13 y 68
        - ans_3_score debe tener un valor de 0 o 1 (los cuales definen si la persona llego temprano o tarde respectivamente)
    Post condiciones:
        - Asigna un caracter por referencia a la variable score alocada en el main
            + Si el final_score es mayor o igual a 13 y menor o igual a 41
                · Si ans_3_score es igual a 0 (llega temprano), asigna el personaje de Stitch al usuario con el resultado del analisis
                · Si ans_3_score es igual a 1 (llega tarde), asigna el personaje de Olaf al usuario con el resultado del analisis
            + Si el final_score es mayor o igual a 42 y menor o igual a 68
                · Si ans_3_score es igual a 0 (llega temprano), asigna el personaje de Jasmin al usuario con el resultado del analisis
                · Si ans_3_score es igual a 1 (llega tarde), asigna el personaje de Rayo al usuario con el resultado del analisis
*/
void character_selector(int final_score, int ans_3_score){
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("\nYa tenemos el resultado del analisis!!!\n");
    if(final_score >= 13 && final_score <= 41){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje - %s -.\n", final_score, S);
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje - %s -.\n", final_score, O);
            printf("          _________________\n");
            printf("         |I like warm hugs!|\n");
            printf("     __  |_________________|\n");
            printf("   _|==|_  v\n");
            printf("    ('')___/\n");
            printf(">--(`^^')\n");
            printf("  (`^'^'`)\n");
            printf("  `======'\n");
        }
    }
    else if(final_score >= 42 && final_score <= 68){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje - %s -.\n", final_score, J);
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje - %s -.\n", final_score, R);
            printf("  ______\n");
            printf(" /|_||_\\`.__\n");
            printf("(   _    _ _\\\n");
            printf("=`-(_)--(_)-'       KUCHAU!\n");
        }
    }
    else{
        printf("\nNo se pudo definir el personaje, por favor intente nuevamente. :(\n");
    }
}


int main(){
    int ans_1_score;
    int ans_2_score;
    int ans_3_score;
    int ans_4_score;

    qst_1(&ans_1_score);
    qst_2(&ans_2_score);
    qst_3(&ans_3_score);
    qst_4(&ans_4_score);


    //printf("\n\nans_1: %i\n", ans_1_score);
    //printf("ans_2: %i\n", ans_2_score);
    //printf("ans_3: %i\n", ans_3_score);
    //printf("ans_4: %i\n\n", ans_4_score);

    //printf("Final Score: %i\n", ans_1_score+(ans_2_score*ans_4_score));

    character_selector(ans_1_score+(ans_2_score*ans_4_score), ans_3_score);

    printf("\n--------------------------------------------------------------------------------------------\n");
    return 0;
}

// compile with: gcc dia_en_la_uni.c -Wall -Werror -Wconversion -std=c99 -o dia_en_la_uni