#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "snakeAPI.h"
#include "Snakestruct.h"

int main() {
	printf("Test\n");
	//Initialise la connexion avec le serveur
	connectToServer("localhost", 1234, "PythonSlayer");
	
	//Attendre que le serveur démarre le jeu
	char gameType[40];
	char gameName[10] = "Partie"; 
	int sizeX = 2;
	int sizeY = 2; 
	int nbWalls = 2;
	waitForSnakeGame(strcpy(gameType,"TRAINING SUPER_PLAYER difficulty=2 "), strcpy(gameName,"Partie"), &sizeX, &sizeY,&nbWalls);
	printf("%d  %d\n", sizeX, sizeY);
	// Récupérer l'emplacement des murs de l'arène et le joueur commence
    int walls[4 * nbWalls];
    int player1 = getSnakeArena(walls);
    int player2 = (player1 + 1) % 2;
    // Boucle de jeu
    Snake* MySnake = malloc(sizeof(Snake));
    Snake* opponentSnake = malloc(sizeof(Snake));
    initializeSnake(MySnake, player1, sizeX, sizeY);
    initializeSnake(opponentSnake, player2, sizeX, sizeY);
    while (1) {
    	//Démarrage du jeu
    	printf("Le jeu commence....\n");
    	//Affichage de l'état actuel de l'arène
    	printArena();
        //printf("position x = %d\n", MySnake->segments->x);
        //printf("position y = %d\n", MySnake->segments->y);
        
        Position* snakePosition = MySnake->segments;
        getSnakePosition(MySnake, snakePosition);

        t_move move;
        bool wallInFront;
        int direction = MySnake->direction;
        for(int i = 0; i < MySnake->length; i++) {
            printf("position x = %d, position y = %d\n", opponentSnake->segments[i].x, opponentSnake->segments[i].y);
        } 
        if (MySnake->move_count == 0){
            direction = ((MySnake->direction + 1) % 4);
        }
        for (int i = 0; i <= 3; i ++) {
            if (isWallInFront(MySnake, walls, nbWalls, direction, sizeX, sizeY) == false){
                if((isSnakeSegmentInFront(MySnake, direction) == false) && (isSnakeInFront(MySnake, opponentSnake, direction) == false) ){
                    move = direction;
                    wallInFront = false;
                    printf("mur non detecter\n");
                    break;
                }
            }
            if ((isWallInFront(MySnake, walls, nbWalls, i, sizeX, sizeY) == false) && (i != ((MySnake->direction + 2) % 4))){
                if ((isSnakeSegmentInFront(MySnake, i) == false) && (isSnakeInFront(MySnake, opponentSnake, i) == false)){
                    move = i;
                    wallInFront = false;
                    printf("mur non detecter\n");
                    break;
                }
            }
            else {
                wallInFront = true;
            } 
        }
        if (!wallInFront) {
            MySnake->direction = move;
            //update_snake(MySnake);
        }
        else {
            printf("Collision detected!\n");
            break;
        }   
        move = MySnake->direction;
        printf("direction = %d\n", move);

        if (player1 == 0){
            // Envoyer le mouvement au serveur
            t_return_code ret = sendMove(move);
            
            if (ret == LOSING_MOVE) {
                printf("Vous avez perdu!\n");
                break;
            } else if (ret == WINNING_MOVE) {
                printf("Félicitations! Vous avez gagné!\n");
                break;
            }

            // Récupérer le mouvement de l'adversaire
            t_move opponentMove;
            ret = getMove(&opponentMove);
            opponentSnake->direction = opponentMove;
            if (ret == LOSING_MOVE) {
                printf("L'adversaire a perdu!\n");
                break;
            } else if (ret == WINNING_MOVE) {
                printf("L'adversaire a gagné!\n");
                break;
            }
        }
        else{
        // Récupérer le mouvement de l'adversaire
            t_move opponentMove;
            t_return_code ret = getMove(&opponentMove);
            opponentSnake->direction = opponentMove;
            if (ret == LOSING_MOVE) {
                printf("L'adversaire a perdu!\n");
                break;
            } else if (ret == WINNING_MOVE) {
                printf("L'adversaire a gagné!\n");
                break;
            }

            // Envoyer le mouvement au serveur
            ret = sendMove(move);
            if (ret == LOSING_MOVE) {
                printf("Vous avez perdu!\n");
                break;
            } else if (ret == WINNING_MOVE) {
                printf("Félicitations! Vous avez gagné!\n");
                break;
            }
        }
        update_snake(MySnake);
        update_snake(opponentSnake);
        
    }
    //printf("taille du Snake %d\n", MySnake->length);
	free(MySnake);
	//Ferme la connection avec le serveur 
	closeConnection();
	return 0;
}
