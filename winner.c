#include "poker_header.h"


/*Determine winner of this game, I only account for a single winner, or tie between two players*/

void findWinner(Player * nPlayer, double * pot){
	int i, mark, win, first, second;
	float max;
	float result;
	first = second = 100;
	max = 0;
	mark = 0;
	for (i = 0; i < PLAYERS; i++){
		if (nPlayer[i].inGame == 1){
			result = analyze_hand(nPlayer[i]);
			
			/*Here I determine if the player's result is uniquely high, or ties a previous max*/
			if (result > max){
				win = 1;
				max = result;
				mark = i;
			}
			else if (result == max){
				win = 2;
				mark = i;
			}
		}
	}

/*If there is a tie then need to find who tied*/
	if (win == 2){
		mark = 0;
		for (i = 0; i < PLAYERS; i++){
			if (nPlayer[i].inGame == 1){	
				result = analyze_hand(nPlayer[i]);
				if (result == max && first == 100){
					first = i;
					}
				else if (result == max && second == 100){
					second = i;
				}
			}
		}
		/*Split the pot between the two winners*/
		printf("%s and %s have tied and will split the pot of %.2lf\n", nPlayer[first].name, nPlayer[second].name, *pot);
		nPlayer[first].galleons = nPlayer[first].galleons + (*pot/2);
		nPlayer[second].galleons = nPlayer[second].galleons + (*pot/2);
	}
	else{
	/*If only one winner, then then win the whole pot*/
		printf("\n%s has won %.2lf\n\n", nPlayer[mark].name, *pot);
		nPlayer[mark].galleons = nPlayer[mark].galleons + *pot;	
		printf("%s had a hand of:\n", nPlayer[mark].name);
		for (i = 0; i< HAND; i++){
			printf("%d) %s\t%s\n", i, nPlayer[mark].hand[i].face, nPlayer[mark].hand[i].suit);
		}
	}
}


