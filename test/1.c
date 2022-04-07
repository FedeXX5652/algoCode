#include <stdio.h>

int main(){
    int exam_score = 0;
    int score = 0;
    printf("Ingrese el valor de su nota en entero (1-10): ");

    // Espero la respuesta
    scanf(" %d", &exam_score);

    // Verifico la respuesta con las condiciones dadas y re pregunto en caso de no ser correcta
    while(exam_score < 1 || exam_score > 10){
        printf("\nIngrese una nota valida: ");
        scanf(" %d", &exam_score);
    }

    printf("Valor de la nota: %d\n", exam_score);

    if(exam_score <= 1 && exam_score >= 3){
        (score) = 1;
    }
    else if(exam_score >= 4 && exam_score <= 6){
        (score) = 2;
    }
    else if(exam_score >= 7 && exam_score <= 8){
        (score) = 3;
    }
    else if(exam_score >= 9 && exam_score <= 10){
        (score) = 4;
    }

    printf("Socre from qst_4: %d\n", (score));
}
