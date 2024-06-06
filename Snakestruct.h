#define MAX_SNAKE_LENGTH 100

typedef struct {
    int x;
    int y;
} Position;

typedef struct {
    int id;
    Position segments[MAX_SNAKE_LENGTH];
    int length;
    int direction;
    int move_count;
} Snake;



void initializeSnake(Snake* snake, int id, int sizeX, int sizeY) ;

bool isWallInFront(Snake* snake, int* walls, int nbW, int snake_direction, int sizeX, int sizeY) ;

bool isSnakeInFront(Snake* snake, Snake* opponent, int snake_direction);

bool isSnakeSegmentInFront(Snake* snake, int snake_direction) ;

void update_snake(Snake* snake) ;


void getSnakePosition(Snake* snake, Position* position) ;