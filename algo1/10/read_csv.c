#include <stdio.h>
#include <stdlib.h>

#define MAX 100

#define READ_FORMAT "%[^;];%lf;%i;%lf;%lf;%lf;%lf;%i;%[^\n]\n"
#define PRINT_FORMAT "Name: %s, MPG: %lf, Cylinders: %i, Displacement: %lf, HP: %lf, Weight: %lf, Acceleration: %lf, Model: %i, Origin: %s\n\n----------------------------------------------------\n"

typedef struct car {
    char name[MAX];
    double mpg;
    int cyl;
    double disp;
    double hp;
    double weight;
    double acceleration;
    int model;
    char origin[MAX];
} car_t;

void print_car(car_t car){
    printf(PRINT_FORMAT, car.name, car.mpg, car.cyl, car.disp, car.hp, car.weight, car.acceleration, car.model, car.origin);
}

int main(int argc, char *argv[]){
    printf("argv 1: %s\n", argv[1]);
    FILE* f_cars = fopen(argv[1], "r");     //open file
    if(f_cars == NULL){                //if file doesn't exist
        perror("Error opening file\n");
        return 1;
    }
    else{
        printf("File opened\n");
    }

    // Car;MPG;Cylinders;Displacement;Horsepower;Weight;Acceleration;Model;Origin
    // STRING;DOUBLE;INT;DOUBLE;DOUBLE;DOUBLE;DOUBLE;INT;CAT

    car_t car;

    int leidos = fscanf(f_cars, READ_FORMAT, car.name, &car.mpg, &car.cyl, &car.disp, &car.hp, &car.weight, &car.acceleration, &car.model, car.origin);

    while(leidos != EOF){
        print_car(car);
        leidos = fscanf(f_cars, READ_FORMAT, car.name, &car.mpg, &car.cyl, &car.disp, &car.hp, &car.weight, &car.acceleration, &car.model, car.origin);
    }

    fclose(f_cars);
    return 0;
}