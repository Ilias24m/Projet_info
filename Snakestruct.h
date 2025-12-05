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
    int possible_directions[4];
} Snake;



void initializeSnake(Snake* snake, int id, int sizeX, int sizeY) ;

bool isWallInFront(Snake* snake, int* walls, int nbW, int snake_direction, int sizeX, int sizeY) ;

bool isSnakeInFront(Snake* snake, Snake* opponent, int snake_direction);

bool isSnakeSegmentInFront(Snake* snake, int snake_direction) ;

void update_snake(Snake* snake) ;

bool check_walls_and_snakes(Snake* MySnake, Snake* opponentSnake, int direction, int* walls, int nbWalls, int sizeX, int sizeY, int N) ;

int future_collision(Snake* MySnake, Snake* opponentSnake, int direction, int* walls, int nbWalls, int sizeX, int sizeY, int futureSteps);

void make_move(Snake* MySnake, Snake* opponentSnake, int* walls, int nbWalls, int sizeX, int sizeY, int futureSteps);