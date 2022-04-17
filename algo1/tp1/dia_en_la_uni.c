#include <stdio.h>
#include <ctype.h>

//#define getName(var)  #var      // me permite obtener el nombre de la variable, getName(J) devuelve "J"

#define JASMIN "Jasmín"
#define RAYO "Rayo McQueen"
#define OLAF "Olaf"
#define STITCH "Stitch"

#define TRINEO 'T'
#define NAVE 'N'
#define CAMION 'C'
#define ALFOMBRA 'A'

#define BOLA_DE_NIEVE 'B'
#define PIUM_PIUM 'P'
#define KUCHAU 'K'
#define GENIO  'G'


/*
    Precondiciones:
        -
    Postcondiciones:
        - Requiere que el usuario ingrese alguno de los valores indicados (T, N, C, A)
        - Guarda el resultado en la variable ans en caso de ser correcto
*/
void validate_ans_1(char* ans){

    scanf(" %c", ans);
    *ans = (char)toupper(*ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(*ans != TRINEO && *ans != NAVE && *ans != CAMION && *ans != ALFOMBRA){
        printf("Ingrese una respuesta válida: ");
        scanf(" %c", ans);
        *ans = (char)toupper(*ans);
    }
}

/*
    Precondiciones:
        -

    Postcondiciones:
        - Asigna un valor por referencia a la variable score con el puntaje correspondiente
*/
void qst_1(int* score){
    char ans;

    // Realizo la pregunta 1
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Trineo (%c)\n", TRINEO);
    printf("2. Nave (%c)\n", NAVE);
    printf("3. Camión (%c)\n", CAMION);
    printf("4. Alfombra (%c)\n\n", ALFOMBRA);

    validate_ans_1(&ans);

    // Asigno un score a la respuesta
    if(ans == TRINEO || ans == NAVE){
        *score = 10;
    }
    else if(ans == CAMION || ans == ALFOMBRA){
        *score = 20;
    }

    //printf("Socre from qst_1: %d\n", *score);
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese alguno de los valores indicados (B, P, K, G)
        - Guarda el resultado en la variable ans en caso de ser correcto
*/

void validate_ans_2(char* ans){
    scanf(" %c", ans);
    *ans = (char)toupper(*ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(*ans != BOLA_DE_NIEVE && *ans != PIUM_PIUM && *ans != KUCHAU && *ans != GENIO){
        printf("Ingrese una respuesta válida: ");
        scanf(" %c", ans);
        *ans = (char)toupper(*ans);
    }
}

/*
    Precondiciones:
        -

    Postcondiciones:G)
        - Asigna un valor por referencia a la variable score con el puntaje correspondiente
            + Si la respuesta es "B" (Bola de nieve), el puntaje es de 3
            + Si la respuesta es "P" (Pium pium), el puntaje es de 6
            + Si la respuesta es "K" (Kuchau), el puntaje es de 9
            + Si la respuesta es "G" (Genio), el puntaje es de 12
*/
void qst_2(int* qst_score){
    char ans;

    // Realizo la pregunta 2
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Bola de nieve (%c)\n", BOLA_DE_NIEVE);
    printf("2. Pium pium (%c)\n", PIUM_PIUM);
    printf("3. Kuchau (%c)\n", KUCHAU);
    printf("4. Genio (%c)\n\n", GENIO);


    validate_ans_2(&ans);

    // Asigno un score a la respuesta
    if(ans == BOLA_DE_NIEVE){
        (*qst_score) = 3;
    }
    else if(ans == PIUM_PIUM){
        (*qst_score) = 6;
    }
    else if(ans == KUCHAU){
        (*qst_score) = 9;
    }
    else if(ans == GENIO){
        (*qst_score) = 12;
    }

    //printf("Socre from qst_2: %d\n", (*qst_score));
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese un horario valido en forma de FLOAT,
            siendo que la parte entera debe ser entre 0 y 23 (horas), y la parte decimal entre 0 y 59 (minutos)
        - Guarda el resultado en la variable hour_value en caso de ser correcto
*/
void validate_ans_3(float* hour_value){
    scanf(" %f", hour_value);
    int integer = (int)*hour_value;
    int decimal = ((int)(*hour_value-(float)integer))*10;

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(decimal < 0 || decimal > 59 || integer < 0 || integer > 23){
        printf("\nIngrese una hora válida: ");
        scanf(" %f", hour_value);
        integer = (int)*hour_value;
        decimal = ((int)(*hour_value-(float)integer))*10;
    }

}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Asigna un valor por referencia a la variable score con el puntaje correspondiente
            + Si el horario ingresado es menor o igual a 15.30, el puntaje es 0 (llega temprano)
            + Si el horario ingresado es mayor a 15.30, el puntaje es 1 (llega tarde)
*/
void qst_3(int* qst_score){
    float hour_value;

    // Realizo la pregunta 3
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    printf("\nIngrese la hora en forma decimal: ");

    validate_ans_3(&hour_value);

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
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese un valor del 1 al 10 en forma de entero
        - Guarda el resultado en la variable hour_value en caso de ser correcto
*/

void validate_ans_4(int* exam_score){
    scanf(" %i", exam_score);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(*exam_score < 1 || *exam_score > 10){
        printf("\nIngrese una nota válida: ");
        scanf(" %i", exam_score);
    }
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Asigna un valor por referencia a la variable score con el puntaje correspondiente
            + Si el valor ingresado es mayor o igual a 1 y menor o igual a 3, asigna un valor de 1 al score
            + Si el valor ingresado es mayor o igual a 4 y menor o igual a 6, asigna un valor de 2 al score
            + Si el valor ingresado es mayor o igual a 7 y menor o igual a 8, asigna un valor de 3 al score
            + Si el valor ingresado es mayor o igual a 9 y menor o igual a 10, asigna un valor de 4 al score
*/
void qst_4(int* qst_score){
    int exam_score = 0;

    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte?\n");
    printf("Ingrese el valor de su nota en entero (1-10): ");

    validate_ans_4(&exam_score);

    // Asigno un score a la respuesta
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
    Precondiciones:
        - El final_score debe tener un valor entre 13 y 68
        - ans_3_score debe tener un valor de 0 o 1 (los cuales definen si la persona llego temprano o tarde respectivamente)
    
    Postcondiciones:
        - Imprime el resultado del analisis asignando un personaje al usuario
    
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

    // Asigno un personaje al usuario segun el resultado del analisis
    if(final_score >= 13 && final_score <= 41){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, STITCH);
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, OLAF);
        }
    }
    else if(final_score >= 42 && final_score <= 68){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, JASMIN);
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, RAYO);
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

    character_selector(ans_1_score+(ans_2_score*ans_4_score), ans_3_score);

    printf("\n--------------------------------------------------------------------------------------------\n");
    return 0;
}

// compile with: gcc dia_en_la_uni.c -Wall -Werror -Wconversion -std=c99 -o dia_en_la_uni