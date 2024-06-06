#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "snakeAPI.h"
#include "Snakestruct.h"





void initializeSnake(Snake* snake, int id, int sizeX, int sizeY) {
    snake->length = 1;  
    snake->move_count = 9; //TESTER AVEC 1

    if (id == 0) {
        snake->segments[0].x = 2;
        //snake->segments[1].x = 2;
        snake->segments[0].y = sizeY / 2;
        //snake->segments[1].y = sizeY / 2;
        snake->direction = EAST;
    } else if (id == 1) {
        snake->segments[0].x = sizeX - 3;
        //snake->segments[1].x = sizeX - 2;
        snake->segments[0].y = sizeY / 2;
        //snake->segments[1].y = sizeY / 2;
        snake->direction = WEST;
    }
}

//SUPPRIMER SNKAE_DIRECTION
bool isWallInFront(Snake* snake, int* walls, int nbW, int snake_direction, int sizeX, int sizeY) {
    for (int i = 0; i < nbW * 4; i += 4) {
        int x1 = walls[i];
        int y1 = walls[i+1];
        int x2 = walls[i+2];
        int y2 = walls[i+3];

       if (snake_direction == NORTH) {
            if ((((snake->segments->y == y2 && snake->segments->x == x2)&&((snake->segments->y-1 == y1) && snake->segments->x == x1))||((snake->segments->y == y1 && snake->segments->x == x1)&&((snake->segments->y-1 == y2) && snake->segments->x == x2)))||snake->segments->y == 0) {
                printf("mur detecter NORTH\n");
                return true;  // There is a wall in front (North)
            } 
        } else if (snake_direction == EAST) {
            if ((((snake->segments->x == x1 && snake->segments->y == y1)&&((snake->segments->x+1 == x2) && snake->segments->y == y2))||((snake->segments->x == x2 && snake->segments->y == y2)&&((snake->segments->x+1 == x1) && snake->segments->y == y1)))||snake->segments->x == sizeX - 1) {
                printf("mur detecter EAST\n");
                return true;  // There is a wall in front (East)   
            } 
        } else if (snake_direction == SOUTH) {
            if ((((snake->segments->y == y1 && snake->segments->x == x1)&&((snake->segments->y+1 == y2) && snake->segments->x == x2))||((snake->segments->y == y2 && snake->segments->x == x2)&&((snake->segments->y+1 == y1) && snake->segments->x == x1)))||snake->segments->y == sizeY - 1) {
                printf("mur detecter SOUTH\n");
                return true;  // There is a wall in front (South)
            } 
        } else if (snake_direction == WEST) {
            if ((((snake->segments->x == x2 && snake->segments->y == y2)&&((snake->segments->x-1 == x1) && snake->segments->y == y1))||((snake->segments->x == x1 && snake->segments->y == y1)&&((snake->segments->x-1 == x2) && snake->segments->y == y2)))||snake->segments->x == 0) {
                printf("mur detecter WEST\n");
                return true;  // There is a wall in front (West)
                
            }
        } // There is no wall in front
    }
    return false;
}
bool isSnakeInFront(Snake* snake, Snake* opponent, int snake_direction) {
    if (snake_direction == NORTH){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x == opponent->segments[i].x && snake->segments->y - 1 == opponent->segments[i].y) {
                printf("snake detecter NORTH position %d %d\n", opponent->segments[i].x, opponent->segments[i].y);
                return true;
            } 
        }
    } else if (snake_direction == EAST){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x + 1 == opponent->segments[i].x && snake->segments->y == opponent->segments[i].y) {
                printf("snake detecter EAST position %d %d\n", opponent->segments[i].x, opponent->segments[i].y);
                return true;
            } 
        }
    } else if (snake_direction == SOUTH){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x == opponent->segments[i].x && snake->segments->y + 1 == opponent->segments[i].y) {
                printf("snake detecter SOUTH position %d %d\n", opponent->segments[i].x, opponent->segments[i].y);
                return true;
            } 
        }
    } else if (snake_direction == WEST){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x - 1 == opponent->segments[i].x && snake->segments->y == opponent->segments[i].y) {
                printf("snake detecter WEST position %d %d\n", opponent->segments[i].x, opponent->segments[i].y);
                return true;
            }  
        }
    }

     return false;  
}


//SUPPRIMER SNAKE_DIRECTION
bool isSnakeSegmentInFront(Snake* snake, int snake_direction) {
    if (snake_direction == NORTH){
        for (int i = 0; i < snake->length; i++) {
            if ((snake->segments->x == snake->segments[i].x) && ((snake->segments->y - 1) == snake->segments[i].y)) {
                
                printf("snake detecter NORTH position %d %d\n", snake->segments[i].x, snake->segments[i].y);
                return true;
                
            } 
    } 
    } else if (snake_direction == EAST){
        for (int i = 0; i < snake->length; i++) {
            if (((snake->segments->x + 1) == snake->segments[i].x) && (snake->segments->y == snake->segments[i].y)) {
                    printf("snake detecter EAST position %d %d\n", snake->segments[i].x, snake->segments[i].y);
                    return true;
            } 
        }
    } else if (snake_direction == SOUTH){
        for (int i = 0; i < snake->length; i++) {
            if ((snake->segments->x == snake->segments[i].x) && ((snake->segments->y + 1) == snake->segments[i].y)) {
                    printf("snake detecter SOUTH position %d %d\n", snake->segments[i].x, snake->segments[i].y);
                    return true;
            } 
        }
    } else if (snake_direction == WEST){
        for (int i = 0; i < snake->length; i++) {
            if (((snake->segments->x - 1) == snake->segments[i].x) && (snake->segments->y == snake->segments[i].y)) {
                    printf("snake detecter WEST position %d %d\n", snake->segments[i].x, snake->segments[i].y);
                    return true;
            }  
        }
    }

     return false;  
}

void update_snake(Snake* snake) {
    Position new_head = snake->segments[0];
    if (snake->direction == NORTH) {
        new_head.y -= 1;
    } else if (snake->direction == EAST) {
        new_head.x += 1;
    } else if (snake->direction == SOUTH) {
        new_head.y += 1;
    } else if (snake->direction == WEST) {
        new_head.x -= 1;
    }

    for (int i = snake->length; i > 0; i--) {
        snake->segments[i] = snake->segments[i - 1];
    }
    snake->segments[0] = new_head;
    // Increment move count
    snake->move_count++;

    // Augmentez la longueur du serpent si nécessaire
    if (snake->move_count >=10) {
        if(snake->length < MAX_SNAKE_LENGTH) {
            snake->length += 1;
        }
        snake->move_count = 0;        
    }



    //printf("Snake length: %d\n", snake->length);
}

//SUPPRIMER CETTE FONTION
void getSnakePosition(Snake* snake, Position* position) {
    position->x = snake->segments->x;
    position->y = snake->segments->y;
}