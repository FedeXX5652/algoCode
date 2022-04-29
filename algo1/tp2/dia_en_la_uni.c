#include <stdio.h>
#include <ctype.h>

const char *JASMIN_NAME = "Jasmín";
const char *RAYO_NAME = "Rayo McQueen";
const char *OLAF_NAME = "Olaf";
const char *STITCH_NAME = "Stitch";

const char STITCH_ID = 'S';
const char JASMIN_ID = 'J';
const char RAYO_ID = 'R';
const char OLAF_ID = 'O';

const char TRINEO_ID = 'T';
const char NAVE_ID = 'N';
const char CAMION_ID = 'C';
const char ALFOMBRA_ID = 'A';

const char BOLA_DE_NIEVE_ID = 'B';
const char PIUM_PIUM_ID = 'P';
const char KUCHAU_ID = 'K';
const char GENIO_ID = 'G';


//-------------------------------------------------------------------------------------------------------------------------------------------------------
//    PREGUNTAS
//-------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese alguno de los valores indicados (T, N, C, A)
        - Retorna ans, el caracter de la respuesta ingresada
*/
char qst_1(){
    char ans;

    // Realizo la pregunta 1
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Estás saliendo de tu casa, y te enteras que hay paro de trenes, ¿Qué otro transporte elegís?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Trineo (%c)\n", TRINEO_ID);
    printf("2. Nave (%c)\n", NAVE_ID);
    printf("3. Camión (%c)\n", CAMION_ID);
    printf("4. Alfombra (%c)\n\n", ALFOMBRA_ID);

    // Espero la respuesta
    scanf(" %c", &ans);
    ans = (char)toupper(ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(ans != TRINEO_ID && ans != NAVE_ID && ans != CAMION_ID && ans != ALFOMBRA_ID){
        printf("Ingrese una respuesta valida: ");
        scanf(" %c", &ans);
        ans = (char)toupper(ans);
    }

    return ans;
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese alguno de los valores indicados (B, P, K, G)
        - Retorna ans, el caracter de la respuesta ingresada
*/
char qst_2(){
    char ans;

    // Realizo la pregunta 2
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("En medio del camino te encontras con una manifestación, ¿Que medio utilizas para deshacerte de la manifestación?\n");
    printf("Ingrese el cartacter correspondiente a la respuesta elegida EN MAYUSCULA:\n\n");
    printf("1. Bola de nieve (%c)\n", BOLA_DE_NIEVE_ID);
    printf("2. Pium pium (%c)\n", PIUM_PIUM_ID);
    printf("3. Kuchau (%c)\n", KUCHAU_ID);
    printf("4. Genio (%c)\n\n", GENIO_ID);

    // Espero la respuesta
    scanf(" %c", &ans);
    ans = (char)toupper(ans);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(ans != BOLA_DE_NIEVE_ID && ans != PIUM_PIUM_ID && ans != KUCHAU_ID && ans != GENIO_ID){
        printf("Ingrese una respuesta valida: ");
        scanf(" %c", &ans);
        ans = (char)toupper(ans);
    }

    return ans;
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese un numero el fomra de float representando la hora de llegada (hh.mm) siendo:
            + hh: horas (entre 0 y 23)
            + mm: minutos (entre 0 y 59)
        - Retorna hour_value, el valor de tipo float de la hora de llegada
*/
float qst_3(){
    float hour_value;

    // Realizo la pregunta 3
    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Lograste superar la manifestación, ¿A qué hora conseguiste llegar a la universidad?\n");
    printf("\nIngrese la hora en forma decimal: ");

    // Espero la respuesta
    scanf(" %f", &hour_value);
    int integer = (int)hour_value;
    float decimal = (hour_value-(float)integer);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(!(decimal >= 0 && decimal <= 0.59 && integer >= 0 && integer <= 23)){
        printf("\nIngrese una hora valida: ");
        scanf(" %f", &hour_value);
        integer = (int)hour_value;
        decimal = ((hour_value-(float)integer));
    }

    return hour_value;
}


/*
    Precondiciones:
        -

    Postcondiciones:
        - Requiere que el usuario ingrese un valor del 1 al 10 en forma de entero
        - Retorna exam_score, el valor de tipo int de la respuesta ingresada
*/
int qst_4(){
    int exam_score = 0;

    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("Por fin llegó la nota del parcial! ¿Qué nota lograste sacarte?\n");
    printf("Ingrese el valor de su nota en entero (1-10): ");

    // Espero la respuesta
    scanf(" %d", &exam_score);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(exam_score < 1 || exam_score > 10){
        printf("\nIngrese una nota valida: ");
        scanf(" %d", &exam_score);
    }

    return exam_score;
}


//----------------------------------------------------------------------------------------------------------------------
//                      CALCULO DE SCORE POR PREGUNTA
//----------------------------------------------------------------------------------------------------------------------

/*
    Precondiciones:
        - Requiere que el qst_1_response contenga de los valores indicados (T, N, C, A)

    Postcondiciones:
        - Asigna un numero entero por referencia a la variable qst_1_score que representa la cantidad de puntos obtenidos
*/
void qst_1_get_score(int* qst_1_score, char* qst_1_response){
    if(*qst_1_response == TRINEO_ID || *qst_1_response == NAVE_ID){
        *qst_1_score = 10;
    }
    else if(*qst_1_response == CAMION_ID || *qst_1_response == ALFOMBRA_ID){
        *qst_1_score = 20;
    }
}


/*
    Precondiciones:
        - Requiere que el qst_2_response contenga de los valores indicados (B, P, K, G)

    Postcondiciones:
        - Asigna un numero entero por referencia a la variable qst_2_score que representa la cantidad de puntos obtenidos
*/
void qst_2_get_score(int* qst_2_score, char* qst_2_response){
    if(*qst_2_response == BOLA_DE_NIEVE_ID){
        *qst_2_score = 3;
    }
    else if(*qst_2_response == PIUM_PIUM_ID){
        *qst_2_score = 6;
    }
    else if(*qst_2_response == KUCHAU_ID){
        *qst_2_score = 9;
    }
    else if(*qst_2_response == GENIO_ID){
        *qst_2_score = 12;
    }
}


/*
    Precondiciones:
        - Requiere que el qst_3_response contenga un valor de tipo float
    
    Postcondiciones:
        - Asigna un numero entero por referencia a la variable qst_3_score que representa la cantidad de puntos obtenidos
*/
void qst_3_get_score(int* qst_3_score, float* qst_3_response){
    if(*qst_3_response<=15.30){
        *qst_3_score = 0;     // 0 equivale a llegar temprano
    }
    else if(*qst_3_response>15.30){
        *qst_3_score = 1;     // 1 equivale a llegar tarde
    }
}


/*
    Precondiciones:
        - Requiere que el qst_4_response contenga un valor de tipo entero entre 1 y 10

    Postcondiciones:
        - Asigna un numero entero por referencia a la variable qst_4_score que representa la cantidad de puntos obtenidos
*/
void qst_4_get_score(int* qst_4_score, int* qst_4_response){
    if(*qst_4_response >= 1 && *qst_4_response <= 3){
        (*qst_4_score) = 1;
    }
    else if(*qst_4_response >= 4 && *qst_4_response <= 6){
        (*qst_4_score) = 2;
    }
    else if(*qst_4_response >= 7 && *qst_4_response <= 8){
        (*qst_4_score) = 3;
    }
    else if(*qst_4_response >= 9 && *qst_4_response <= 10){
        (*qst_4_score) = 4;
    }
}


//----------------------------------------------------------------------------------------------------------------------
//                                            CALCULO DE PUNTAJE FINAL
//----------------------------------------------------------------------------------------------------------------------

/*
    Precondiciones:
        - El final_score debe tener un valor entre 13 y 68
        - ans_3_score debe tener un valor de 0 o 1 (los cuales definen si la persona llego temprano o tarde respectivamente)
    
    Postcondiciones:
        - Imprime el resultado del analisis asignando un personaje al usuario
*/
char character_selector(int final_score, int ans_3_score){
    char character;

    printf("\n--------------------------------------------------------------------------------------------\n");
    printf("\nYa tenemos el resultado del analisis!!!\n");
    if(final_score >= 13 && final_score <= 41){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, STITCH_NAME);
            character = STITCH_ID;
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, OLAF_NAME);
            character = OLAF_ID;
        }
    }
    else if(final_score >= 42 && final_score <= 68){
        if(ans_3_score == 0){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, JASMIN_NAME);
            character = JASMIN_ID;
        }
        else if(ans_3_score == 1){
            printf("Con un puntaje de %d puntos se definió el personaje -%s-.\n", final_score, RAYO_NAME);
            character = RAYO_ID;
        }
    }
    else{
        printf("\nNo se pudo definir el personaje, por favor intente nuevamente. :(\n");
    }

    return character;
}


//----------------------------------------------------------------------------------------------------------------------
//                                                    MAIN
//----------------------------------------------------------------------------------------------------------------------

char elegir_personaje(){
    char qst_1_response  = qst_1();
    char qst_2_response  = qst_2();
    float qst_3_response = qst_3();
    int qst_4_response   = qst_4();

    int qst_1_score;
    int qst_2_score;
    int qst_3_score;
    int qst_4_score;


    qst_1_get_score(&qst_1_score, &qst_1_response);
    qst_2_get_score(&qst_2_score, &qst_2_response);
    qst_3_get_score(&qst_3_score, &qst_3_response);
    qst_4_get_score(&qst_4_score, &qst_4_response);

    char selected_character = character_selector(qst_1_score+(qst_2_score*qst_4_score), qst_3_score);

    printf("\n--------------------------------------------------------------------------------------------\n");
    return selected_character;
}

// compile with: gcc dia_en_la_uni.c -Wall -Werror -Wconversion -std=c99 -o dia_en_la_uni