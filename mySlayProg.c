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
	char gameType[30];
	char gameName[10] = "Partie"; 
	int sizeX = 2;
	int sizeY = 2; 
	int nbWalls = 2;
	waitForSnakeGame(strcpy(gameType,"TRAINING RANDOM_PLAYER"), strcpy(gameName,"Partie"), &sizeX, &sizeY,&nbWalls);
	
	// Récupérer l'emplacement des murs de l'arène et le joueur commence
    int walls[4 * nbWalls];
    int player = getSnakeArena(walls);
    // Boucle de jeu
    Snake* MySnake = malloc(sizeof(Snake));
    initializeSnake(MySnake, player, 1, 1);
    while (1) {
    	//Démarrage du jeu
    	printf("Le jeu commence....\n");
    	//Affichage de l'état actuel de l'arène
    	printArena();
        
        Position* snakePosition = MySnake->segments;
        getSnakePosition(MySnake, snakePosition);

        t_move move;
        for (int i = 2; i < 3; i ++) {
            if (isWallInFront(MySnake, walls, nbWalls, i) == false) {
                MySnake->direction = i;
                move = MySnake->direction;
                break;
            } 
        }
        update_snake(MySnake);

        if (player == 0){
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
        
    }
	free(MySnake);
	//Ferme la connection avec le serveur 
	closeConnection();
	return 0;
}
