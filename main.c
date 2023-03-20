#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char regno[7];
    int year;
}CAR;

typedef struct {
    int antal;
    CAR cars[10000000];
} CAR_DATA;

void genRegNo(char *buffer){
    buffer[0] =  'A' + (rand() % 26);
    buffer[1] =  'A' + (rand() % 26);
    buffer[2] =  'A' + (rand() % 26);
}

int genYear(){
    return rand()%(2023-1990) + 1990;
}


int main(){
    srand(time(NULL));

    CAR_DATA allCars;
    char regno[7];
    for(int i = 0; i < 10000000; i++){
        genRegNo(regno);
        strcpy(allCars.cars[i].regno,regno);
        allCars.cars[i].year = genYear();
    }

    return 0;
}
