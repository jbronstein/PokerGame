#include "poker_header.h"

int main(){
	float result;
	char userName [40];
	int i, count, choice, betMarker, pLeft;
	double bet, pot;
	Player newPlayers [PLAYERS];

	/*Intro for the game*/
	setup(newPlayers, userName);
	Deck newDeck;
	srand(time(NULL));
	
	/*MAIN GAME LOOP, BASED ON GALLEONS*/

	while (newPlayers[0].galleons >= 5){
		printf("\n\n========  NEW ROUND  ========\n\n\n");
		pot = bet = 0;

		/*Always update each player to be in the game initially, unless they have less than 5 galleons*/
		for(i = 0; i<PLAYERS; i++){
			newPlayers[i].inGame = 1;
			if (newPlayers[i].galleons < 5){
				newPlayers[i].galleons = 0;
				newPlayers[i].inGame = 0;
				newPlayers[i].checkBet = 0;
			}
			newPlayers[i].checkBet = 0;
			newPlayers[i].galleons = newPlayers[i].galleons - 5;
			if(newPlayers[i].inGame == 1){
				pot = pot + 5;
			}
		}
		/*if the three computers are out of the game, user has won, so end the game!*/
		pLeft = 0;
		for (i = 1; i<PLAYERS; i++){
			if (newPlayers[i].inGame == 0){
				pLeft++;
			}
			if (pLeft == 3){
				printf("\n\nCONGRATULATIONS %s, you won! Harry, Voldy and Dumbly seem to have lost all their money!!!\n\n", newPlayers[0].name);
				return 0;
			}
		}


		sleep(2);
		/*Print out current standings, how many galleons each player has and if they are still in*/	
		printf("Current Standings:\n\n");
		for (i = 0; i<PLAYERS; i++){
			if (newPlayers[i].inGame == 1){
				printf("%s has %.2f Galleons\n", newPlayers[i].name, newPlayers[i].galleons);
			}
		}
		for (i = 0; i<PLAYERS; i++){
			if (newPlayers[i].inGame == 0){
				printf("%s is out of the game\n", newPlayers[i].name);
			}
		}

		/*Initialize Game*/
		fillDeck(&newDeck);
		shuffleDeck(&newDeck);
		dealOut(&newDeck, newPlayers);
		printf("\nYou are about to receive your hand!\n");
		
		/*User specifics*/
		sleep(1);
		displayHand(newPlayers);	
		result = MC_rate(newPlayers, 0);
		sleep(1);

		/*Monte Carlo Advice in MC.c*/
		advice(&newPlayers[0]);

		/*This exchange is only for the user, computers have its own function*/
		exchangeCards(newPlayers, &newDeck);
		displayHand(newPlayers);
		printf("\nYou can now either: \n1) Place a Bet\n2) Pass\n3) Fold\nPlease type 1,2, or 3: ");
		scanf("%d", &choice);
		if (choice == 1){
			bet = placeBet(newPlayers, &pot);
		}
		else if (choice == 3){
			endPlayer(newPlayers, 0);
		}
		else if (choice == 2){
			printf("You have chosen to pass.\n");
		}

		/*run Computer exchanges and whether they decide to raise, pass or fold*/	
		count = 1;
		while (count <= 3){
			if(newPlayers[count].inGame == 1){
				
				sleep(1);
				/*result value is more for testing purposes, but still needs to run to fill in the correct*/
				/*int array mcAdivce for Monte carlo advice for each computer*/
				result = MC_rate(newPlayers, count);
				
				/*This can be found in exchange.c, just exchange based on MC advice*/
				computerExchange(newPlayers, &newDeck, count);
				
				/*This can be found in display.c, determines for the computer what to do (raise, pass, fold)*/
				comp_decision(newPlayers, count, &bet, &pot);
				
				/*keep track of which computer raises for later*/
				if (newPlayers[count].checkBet > 0){
					betMarker = count;
				}
			}

			count++;
		}


		/*if any computer raises, then go back to user one time to either match or fold, then each computer*/

		if (betMarker > 0){
			if (newPlayers[0].galleons < newPlayers[betMarker].checkBet){
				printf("\nOH NOOOO, the bet is more than you can afford, and by wizarding rules, you lose the game!!!\n\n");
					return 0;
			}
		if (newPlayers[0].inGame != 0){	
		printf("%s raised by %.2lf. Would you like to either:\n1) Match\n2) Fold \nPlease type 1 or 2: ", newPlayers[betMarker].name, newPlayers[betMarker].checkBet);
		scanf("%d", &choice);
			if (choice == 1){
				newPlayers[0].galleons = newPlayers[0].galleons - newPlayers[betMarker].checkBet;
				pot = pot + newPlayers[betMarker].checkBet;
				printf("You have matched the raise\n");
			}
			else {
				newPlayers[0].inGame = 0;
				printf("You Folded\n");
			}
			}

	/*Determine whether each computer should match or fold*/	
		for (i = 1; i<betMarker; i++){
			if (newPlayers[i].inGame == 1){
				if (newPlayers[i].galleons > newPlayers[betMarker].checkBet){
					result = analyze_hand(newPlayers[i]);
					if (result < 23){
						newPlayers[i].inGame = 0;
						printf("%s has folded\n", newPlayers[i].name);
					}
					else{	
						newPlayers[i].galleons = newPlayers[i].galleons - newPlayers[betMarker].checkBet;	
						pot = pot + newPlayers[betMarker].checkBet;
						printf("%s has matched the raise\n",newPlayers[i].name);
						}
					}
				}
			}
		}
		
		sleep(2);
		/*find winner of the game, give winning's to rightful winner, display winner's hand*/
		findWinner(newPlayers, &pot);
		
		/*reset betMarker for next game*/
		betMarker = 0;
		sleep(2);
	}

	/*After game loop, you have lost all your money or you have less than the 5 Galleon entrance amount*/	
		printf("\n\nOH NO, you lost at Wizard's poker!!!!\n");
		printf("Final Galleon Count for each player:\n");
		for (i = 0; i < PLAYERS; i++){
			if (newPlayers[i].galleons < 0){
				newPlayers[i].galleons = 0;
			}
			printf("\t%s has %.2f Galleons\n", newPlayers[i].name, newPlayers[i].galleons);
		}

	return 0;
}

