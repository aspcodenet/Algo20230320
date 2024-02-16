#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//Hello
void genRegNo(char *buffer);

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

int calculateNextVersion(int j){
    if(j == 12 || j < 0){
        return j+10;
    }
    return j+1;
}

int genYear(void){
    return rand()%(2023-1990) + 1990;
}

 CAR *Find(CAR_DATA *data, char *regno ){
    CAR *find  = NULL;
    for(int i = 0; i < data->antal;i++)
    {
        if(!strcmp(regno,data->cars[i].regno)){
            find = &data->cars[i];
            return find;
        }
    }
    return find;
 } 

 CAR *Find2(CAR_DATA *data, char *regno ){
    for(int i = 0; i < data->antal;i++)
    {
        int compare = strcmp(regno,data->cars[i].regno);
        if(compare == 0) return &data->cars[i];
        if(compare<0) return NULL;
    }
    return NULL;
 } 


 int compare(const void *s1, const void *s2)
{
  CAR *e1 = (CAR *)s1;
  CAR *e2 = (CAR *)s2;
  return strcmp(e1->regno, e2->regno);
}



#define ROWS 10 //
#define COLS 30 //
#define WALL '#'

typedef struct{
    int X;
    int Y;
}Snake;

typedef enum {
    Snake_Direction_Left,    
    Snake_Direction_Right,
    Snake_Direction_Up,
    Snake_Direction_Down,
}Snake_Direction;

#define clrscr() printf("\e[1;1H\e[2J")

char getch(){
    char c;
    c= getchar();
    return(c);
}



void gotoxy(int x,int y){
//What
    printf("%c[%d;%df",0x1B,y,x);
}

void drawBoundaries(){
    for(int row = 0; row < ROWS+2;row++){
        for(int col = 0; col < COLS+2; col++){
            if(row == 0 || row == ROWS+1 || col == 0 || col == COLS+1){
                printf("%c",WALL);         
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        
    }
}

void drawSnake(Snake snake){
    gotoxy(snake.X,snake.Y);
    printf("@");

}

Snake_Direction getNextSnakeDirection(Snake_Direction currentSnakeDirection){
    gotoxy(0,ROWS+3);
    printf("Ange vad den ska göra:");
    char ch = getch(); // 
    fflush(stdin);
    if(ch == 'u') return Snake_Direction_Up;
    if(ch == 'd') return Snake_Direction_Down;
    if(ch == 'l') return Snake_Direction_Left;
    if(ch == 'r') return Snake_Direction_Right;
    return currentSnakeDirection;

}


void moveSnake(Snake *snake,Snake_Direction direction){
    if(direction == Snake_Direction_Up){
        if(snake->Y == 2) snake->Y = ROWS+1;
        else snake->Y--;
    }
    if(direction == Snake_Direction_Down){
        if(snake->Y == ROWS+1) snake->Y = 2;
        else snake->Y++;
    }
    if(direction == Snake_Direction_Left){
        if(snake->X == 2) snake->X = COLS+1;
        else snake->X--;
    }
    if(direction == Snake_Direction_Right){
        if(snake->X == COLS+1) snake->X = 2;
        else snake->X++;
    }

}






void runGame(){
    Snake snake; // snake är en array med kroppsdelar - varje kroppsdel har en X och en Y
                    //   arrayen[0] = huvudet  12,10   array[1] = 11,10 array[2]=9,10
                        //           @@@
                        //             @@@@@  
    snake.X = 5;
    snake.Y = 5;

    Snake_Direction currentDirection = Snake_Direction_Right;

    while(1){
        clrscr();    // Motsvarar SLÄCK ALLA LEDS
        drawBoundaries();   // BEHÖVS INTE MNED LED MATRISEN
        drawSnake(snake); // Tänd LEDDEN där den är
        // om tryckt på u snake.Y = snake.Y - 1
        gotoxy(0,0);
        currentDirection = getNextSnakeDirection(currentDirection);
        moveSnake(&snake,currentDirection);

        // sleep
    }


}


void startMenu(){
    int n;
    int end = 0;
    while(!end){
        printf("1. Run game\n");
        printf("2. Exit\nWhat do you want to do:");
        scanf("%d",&n);
        switch(n){
            case 1:
                printf("Game starting2");
                runGame();
                break;
            case 2:
                end = 1;
                break;
        }
    }
}


int main(){
    srand(time(NULL));

    startMenu();

    CAR_DATA allCars;
    allCars.antal = 90000000;
    allCars.cars = malloc(allCars.antal*sizeof( CAR ));
    char regno[7];
    for(int i = 0; i < allCars.antal ; i++){
        genRegNo(regno);
        strcpy(allCars.cars[i].regno,regno);
        allCars.cars[i].year = genYear();
    }

    qsort(allCars.cars,allCars.antal,sizeof(CAR),compare);

    clock_t start, end;
    double cpu_time_used;
    start = clock();
    CAR *f = Find2(&allCars,allCars.cars[1000].regno);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;    
    printf("took %f seconds to execute \n", cpu_time_used);
    if(f){
        printf("Found");
    }
    start = clock();
    f = Find2(&allCars,allCars.cars[89999999].regno);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;    
    printf("took %f seconds to execute \n", cpu_time_used);
    if(f){
        printf("Found");
    }


    
    return 0;
}
