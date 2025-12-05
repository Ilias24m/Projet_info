#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "snakeAPI.h"
#include "Snakestruct.h"





void initializeSnake(Snake* snake, int id, int sizeX, int sizeY) {
    snake->length = 1;  
    snake->move_count = 9;

    if (id == 0) {
        snake->segments[0].x = 2;
        snake->segments[0].y = sizeY / 2;
        snake->direction = EAST;
    } else if (id == 1) {
        snake->segments[0].x = sizeX - 3;
        snake->segments[0].y = sizeY / 2;
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
                return true;  // There is a wall in front (North)
            } 
        } else if (snake_direction == EAST) {
            if ((((snake->segments->x == x1 && snake->segments->y == y1)&&((snake->segments->x+1 == x2) && snake->segments->y == y2))||((snake->segments->x == x2 && snake->segments->y == y2)&&((snake->segments->x+1 == x1) && snake->segments->y == y1)))||snake->segments->x == sizeX - 1) {
                return true;  // There is a wall in front (East)   
            } 
        } else if (snake_direction == SOUTH) {
            if ((((snake->segments->y == y1 && snake->segments->x == x1)&&((snake->segments->y+1 == y2) && snake->segments->x == x2))||((snake->segments->y == y2 && snake->segments->x == x2)&&((snake->segments->y+1 == y1) && snake->segments->x == x1)))||snake->segments->y == sizeY - 1) {
                return true;  // There is a wall in front (South)
            } 
        } else if (snake_direction == WEST) {
            if ((((snake->segments->x == x2 && snake->segments->y == y2)&&((snake->segments->x-1 == x1) && snake->segments->y == y1))||((snake->segments->x == x1 && snake->segments->y == y1)&&((snake->segments->x-1 == x2) && snake->segments->y == y2)))||snake->segments->x == 0) {
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
                return true;
            } 
        }
    } else if (snake_direction == EAST){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x + 1 == opponent->segments[i].x && snake->segments->y == opponent->segments[i].y) {
                return true;
            } 
        }
    } else if (snake_direction == SOUTH){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x == opponent->segments[i].x && snake->segments->y + 1 == opponent->segments[i].y) {
                return true;
            } 
        }
    } else if (snake_direction == WEST){
        for (int i = 0; i < opponent->length; i++) {
            if (snake->segments->x - 1 == opponent->segments[i].x && snake->segments->y == opponent->segments[i].y) {
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
                
                return true;
                
            } 
    } 
    } else if (snake_direction == EAST){
        for (int i = 0; i < snake->length; i++) {
            if (((snake->segments->x + 1) == snake->segments[i].x) && (snake->segments->y == snake->segments[i].y)) {
                    return true;
            } 
        }
    } else if (snake_direction == SOUTH){
        for (int i = 0; i < snake->length; i++) {
            if ((snake->segments->x == snake->segments[i].x) && ((snake->segments->y + 1) == snake->segments[i].y)) {
                    return true;
            } 
        }
    } else if (snake_direction == WEST){
        for (int i = 0; i < snake->length; i++) {
            if (((snake->segments->x - 1) == snake->segments[i].x) && (snake->segments->y == snake->segments[i].y)) {
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



}





bool check_walls_and_snakes(Snake* MySnake, Snake* opponentSnake, int direction, int* walls, int nbWalls, int sizeX, int sizeY, int val) {
    bool wallInFront = isWallInFront(MySnake, walls, nbWalls, direction, sizeX, sizeY);
    bool snakeInFront = isSnakeInFront(MySnake, opponentSnake, direction);
    bool snakeSegmentInFront = isSnakeSegmentInFront(MySnake, direction);
    if (wallInFront || snakeInFront || snakeSegmentInFront) {
        return true;
    }
    return false;
}


// Fonction pour vérifier les coups futurs
int future_collision(Snake* MySnake, Snake* opponentSnake, int direction, int* walls, int nbWalls, int sizeX, int sizeY, int futureSteps) {
    Snake snake = *MySnake;
    snake.direction = direction;
    bool collision1 = false;
    bool collision2 = false;
    bool collision3 = false;
    int direction1;
    int direction2;
    int direction3;

    int futureCollision = 0;
    for (int i = 0; i < futureSteps; i++) {
        direction1 = snake.direction;
        direction2 = ((direction1 + 1) % 4);
        direction3 = ((direction1 + 3) % 4);
        collision1 = check_walls_and_snakes(&snake, opponentSnake, direction1, walls, nbWalls, sizeX, sizeY, 4);
        collision2 = check_walls_and_snakes(&snake, opponentSnake, direction2, walls, nbWalls, sizeX, sizeY, 4);
        collision3 = check_walls_and_snakes(&snake, opponentSnake, direction3, walls, nbWalls, sizeX, sizeY, 4);
        if (collision1 == true) {
            if(collision2 == true){
                if(collision3 == true){
                    futureCollision = i;
                    break;
                }
                else {
                    snake.direction = direction3;
                    if (i == 0){
                        futureCollision = i;
                        break;
                    }
                }
            }
            else {
                snake.direction = direction2;
                if (i == 0){
                    futureCollision = i;
                    break;
                }
            }
        }
        update_snake(&snake);
        futureCollision = i;
    }
    return futureCollision;
}



void make_move(Snake* MySnake, Snake* opponentSnake, int* walls, int nbWalls, int sizeX, int sizeY, int futureSteps) {
    int directions[4] = {0, 1, 2, 3}; // North, East, South, West
    int direction = MySnake->direction;
    int maxMoves = -1;
    int move = MySnake->direction;
    for (int i = 0; i < 4; i++) {
        if(direction == ((MySnake->direction + 2) % 4)){
            direction = (direction + 1) % 4;
            continue;
        }
        directions[direction]= future_collision(MySnake, opponentSnake, direction, walls, nbWalls, sizeX, sizeY, futureSteps);
        if (directions[direction] > maxMoves) {
            maxMoves = directions[direction];
            move = direction;
        }
        direction = (direction + 1) % 4; // Changer de direction
    }

    MySnake->direction = move;
}