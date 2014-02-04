#include "poker_header.h"

void displayHand (Player * nPlayer){
	int i, j;
	char letters [5] = {'a', 'b', 'c', 'd', 'e'};
	i = j = 0;
	printf("\nYou have the following hand:\n");
	for (j = 0; j < 5; j++){
		printf("%c) %s\t%s\n", letters[j], nPlayer[i].hand[j].face, nPlayer[i].hand[j].suit);
	}
}

/*Only for the User so they can place bets, return that value so each computer can see it*/
double placeBet(Player * nPlayer, double * total){
	double bet;
	printf("You have %.2f Galleons left\n", nPlayer[0].galleons);
	if (nPlayer[0].galleons == 0){
		printf("Oh no! You have no more Galleons. You cannot bet anymore! hopefully everyone passes\n");
		return 0;
	}
	printf("How many Galleons would you like to bet? ");
	scanf("%lf", &bet);
	printf("\n");
	if (bet > nPlayer[0].galleons){
		printf("You do not have enough Galleons for that bet!\n");
		printf("How many Galleons would you like to bet? ");
		scanf("%lf", &bet);
		printf("\n");
	}

	*total = *total + bet;
	nPlayer[0].checkBet = 1;
	nPlayer[0].galleons = nPlayer[0].galleons - bet;
	return bet;
}

/*Stop the player from being in that specific game*/
void endPlayer(Player * nPlayer, int numPlayer){
    nPlayer[numPlayer].inGame = 0;
	}

/*Computer makes decision whether to Pass, Match, Raise, or Fold*/
void comp_decision(Player * nPlayer, int numPlayer, double * uBet, double * pot){
	float result;
	int numRand;
	result = analyze_hand(nPlayer[numPlayer]);

	if (*uBet > 0){
		if (result > 16){
			/*match the raise*/
			if (nPlayer[numPlayer].galleons >= *uBet){
				nPlayer[numPlayer].galleons = nPlayer[numPlayer].galleons - *uBet;
				*pot = *pot + *uBet;
				printf("%s has matched the raise\n", nPlayer[numPlayer].name);
			}
			else{
				/*if computer don't have enough money to match, then computer folds*/
				nPlayer[numPlayer].inGame = 0;
				printf("%s has folded\n", nPlayer[numPlayer].name); 
			}
		}	

		/*fold if there is a bet but computer hand value is less than or equal to 16*/
		else {
			printf("%s has folded!\n", nPlayer[numPlayer].name);
			nPlayer[numPlayer].inGame = 0;
		}

	}

	/*if there hasn't been a bet yet, then computer decides whether to raise or pass*/
	else if (*uBet == 0){
		if (result <=20){
			printf("%s has passed!\n", nPlayer[numPlayer].name);
		}
		if (result > 20 && result <= 30){
			if (nPlayer[numPlayer].galleons >= 5){
				*uBet = 5;
				*pot = *pot + *uBet;
				nPlayer[numPlayer].galleons = nPlayer[numPlayer].galleons - *uBet;
				nPlayer[numPlayer].checkBet = *uBet;
				printf("%s has raised by %.2lf!\n", nPlayer[numPlayer].name, *uBet);
			}
		}
		/*generate random number above 5 for computer bet*/
		numRand = rand() % 15 + 5;
		if (result > 30){
			if (nPlayer[numPlayer].galleons >= numRand){
				*uBet = numRand;
				*pot = *pot + *uBet;
				nPlayer[numPlayer].galleons = nPlayer[numPlayer].galleons - *uBet;
				nPlayer[numPlayer].checkBet = *uBet;
				printf("%s has raised by %.2lf!\n", nPlayer[numPlayer].name, *uBet);
			}
		}
	}	
}
