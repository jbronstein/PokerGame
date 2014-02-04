#include "poker_header.h"

void advice(Player * nPlayer){
	int i, count;
	char * result = (char*)malloc(sizeof(char)*5);
	char *letters [] = {"a", "b", "c", "d", "e"};
	count = 0;
	
	/*Look at the user's mcAdvice array and where there's a one, replace with the letter(card) to exchange*/
	for (i = 0; i<5; i++){
		if(nPlayer[0].mcAdvice[i] == 1){
			result[count] = *letters[i];
			count++;
		}	
	}
	if (count>0){
		 printf("\n\nThe Sorting Hat recomends swapping the following letters: %s\n", result);
	 }

	/*This really only runs if you start with a straight*/
	else printf("\nThe Sorting Hat advises you to keep your cards!");
}

Deck MC_sim_deck(Player * nPlayer, int numPlayer){
	int i, j;
	Card temp;
	Deck sDeck;
	
	/*fill deck as if it were a normal*/
	fillDeck(&sDeck);

	/*Find Player's cards in deck, then remove them so we can run simulations with remaining cards*/
	for (i = 0; i<5; i++){
		for (j = 0; j<52; j++){
			if (nPlayer[numPlayer].hand[i].face == sDeck.stack[j].face){
				if (nPlayer[numPlayer].hand[i].suit == sDeck.stack[j].suit){
					temp = sDeck.stack[0];
					sDeck.stack[0] = sDeck.stack[j];
					sDeck.stack[j] = temp;
					dequeue(&sDeck);
				}
			}	
		}
	}
	/*return the simulation deck with 47 cards that are not in the player's hand*/
	return sDeck;
}

float MC_rate(Player * nPlayer, int numPlayer){
	Deck simDeck;
	float avg, newAvg, sum;
	int i, j, k, max, count, check;

/*Create Monte Carlo Player to test out all simulations*/
	Player MC;
	Player original;
/*I created Player original so I could quickly reconfigure Monte Carlo's original hand after each exchange*/
	for (i = 0; i<5; i++){
		MC.hand[i] = nPlayer[numPlayer].hand[i];
		original.hand[i] = nPlayer[numPlayer].hand[i];
	}

/*Run the MC_sim_deck function above to get the 47 cards we will use for all simulations*/
	simDeck = MC_sim_deck(&MC, numPlayer);
	
/*initialize average to 0*/	
	avg = 0;

/*In this array, if 1 then echange that card, if 0, do NOT exchange the card*/
	int arr [][5] = {
		{0,0,0,0,0},/*0*/
		{1,0,0,0,0},
		{0,1,0,0,0},
		{0,0,1,0,0},
		{0,0,0,1,0},
		{0,0,0,0,1},
		{1,1,0,0,0},
		{1,0,1,0,0},
		{1,0,0,1,0},
		{1,0,0,0,1},
		{0,1,1,0,0},/*10*/
		{0,1,0,1,0},
		{0,1,0,0,1},
		{0,0,1,1,0},
		{0,0,1,0,1},
		{0,0,0,1,1},
		{1,1,1,0,0},
		{1,1,0,1,0},
		{1,1,0,0,1},
		{1,0,1,1,0},
		{1,0,1,0,1},/*20*/
		{1,0,0,1,1},
		{0,1,1,1,0},
		{0,1,1,0,1},
		{0,1,0,1,1},
		{0,0,1,1,1},
		{1,0,1,1,1},
		{1,1,0,1,1},
		{1,1,1,0,1},
		{1,1,1,1,0},
		{0,1,1,1,1},
		{1,1,1,1,1},/*31*/
	};

/*I run through all 32 possible exchanges and run each scenario 10,000 times to find average for each iteration*/
	for (i = 0; i < 32; i++){
		sum = 0;
		check = 0;
		for (j = 0; j < 10000; j++){
			shuffleDeckMC(&simDeck);
			count = 0;
			/*for loop here just goes up the newly shuffled deck depending on # of card exchanges*/
			/*this made everything alot faster and works to the same effect, rare moment of intelligence*/
			for (k=0; k<5; k++){
				if(arr[i][k] == 1){
					MC.hand[k] = simDeck.stack[count];
					count++;
				}
			}
			/*continue adding the value of each hand scenario to sum*/
			check = analyze_hand(MC);
			sum = sum + check;
			/*reset MC's hand to original*/
			for (k = 0; k<5; k++){
				MC.hand[k] = original.hand[k];
			}
		}

	/*update average if this ith iteration creates a higher value expectation*/
		newAvg = (sum/10000);
		if(newAvg > avg){
			max = i;
			avg = newAvg;
		}
	}
	
	/*Keep track of Monte Carlo Advice array(1 or 0) for each player's mcAdvice*/
	for (k = 0; k<5; k++){
		if(arr[max][k] == 1){
			nPlayer[numPlayer].mcAdvice[k] = 1;
		}
		else{
			nPlayer[numPlayer].mcAdvice[k] = 0;
		}
	}
	/*return highest expected average*/
	return avg;
}
