#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
#include "snakeAPI.h"
#include "Snakestruct.h"

int main() {
	printf("NEW GAME\n");
	//Initialise la connexion avec le serveur
	connectToServer("localhost", 1234, "PythonSlayer24");
	
	//Attendre que le serveur démarre le jeu
	char gameType[40];
	char gameName[10] = "Partie"; 
	int sizeX = 2;
	int sizeY = 2; 
	int nbWalls = 2;
	waitForSnakeGame(strcpy(gameType,"TRAINING SUPER_PLAYER difficulty=3"), strcpy(gameName,"Partie"), &sizeX, &sizeY,&nbWalls);
	printf("%d  %d\n", sizeX, sizeY);
	// Récupérer l'emplacement des murs de l'arène et le joueur commence
    int walls[4 * nbWalls];
    int player1 = getSnakeArena(walls);
    int player2 = (player1 + 1) % 2;

    Snake* MySnake = malloc(sizeof(Snake));
    Snake* opponentSnake = malloc(sizeof(Snake));
    initializeSnake(MySnake, player1, sizeX, sizeY);
    initializeSnake(opponentSnake, player2, sizeX, sizeY);
    
    // Boucle de jeu   
    while (1) {
    	//Démarrage du jeu
    	printf("Le jeu commence....\n");
    	//Affichage de l'état actuel de l'arène
    	printArena();

        t_move move;

    

        /////////////////NEW FUNCTION////////////////////////
        int futureSteps = 212; // Nombre de coups à anticiper

        // Appel de la fonction pour faire un mouvement
        make_move(MySnake, opponentSnake, walls, nbWalls, sizeX, sizeY, futureSteps);
        move = MySnake->direction;

        /* - comment: (string) comment to send to the server (max 100 char.)
        */
        
        
        

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

	free(MySnake);
    free(opponentSnake);
    /*char* comment = "GG WP";
    sendComment(comment);*/
	//Ferme la connection avec le serveur 
	closeConnection();
	return 0;
}
