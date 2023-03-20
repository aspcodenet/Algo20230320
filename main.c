#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char regno[7];
    int year;
}CAR;

typedef struct {
    int antal;
    CAR *cars;
} CAR_DATA;

void genRegNo(char *buffer){
    buffer[0] =  'A' + (rand() % 26);
    buffer[1] =  'A' + (rand() % 26);
    buffer[2] =  'A' + (rand() % 26);
    buffer[3] =  '0' + (rand() % 10);
    buffer[4] =  '0' + (rand() % 10);
    buffer[5] =  '0' + (rand() % 10);
    buffer[6] =  0;
}

int genYear(){
    return rand()%(2023-1990) + 1990;
}

 CAR *Find(CAR_DATA *data, char *regno ){
    CAR *find  = NULL;
    for(int i = 0; i < data->antal;i++)
    {
        if(!strcmp(regno,data->cars[i].regno))
            find = &data->cars[i];
    }
    return find;
 } 


int main(){
    srand(time(NULL));

    CAR_DATA allCars;
    allCars.antal = 90000000;
    allCars.cars = malloc(allCars.antal*sizeof( CAR ));
    char regno[7];
    for(int i = 0; i < allCars.antal ; i++){
        genRegNo(regno);
        strcpy(allCars.cars[i].regno,regno);
        allCars.cars[i].year = genYear();
    }

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    CAR *f = Find(&allCars,regno);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;    
    printf("took %f seconds to execute \n", cpu_time_used);

    if(f){
        printf("Found");
    }else{
        printf("Not found");
    }

    
    return 0;
}
