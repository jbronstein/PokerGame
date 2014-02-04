#include "poker_header.h"

/*analyze_hand converts a player's hand into two arrays (face and suit) and keeps track of # of occurences*/
float analyze_hand(Player individual){
	char faceCheck [13];
	char suitCheck [4];
	int i, j, target;
	float result;


	for (i=0; i < 13; i++){
		faceCheck[i] = 0;
	}
	for (i=0; i < 4; i++){
		suitCheck[i] = 0;
	}
	
	for (i = 0; i < HAND; i++){

		/*getNum and getSuit can be found at bottom of this file*/
		target = getNum(individual.hand[i].face);

		for(j = 0; j <13; j++){
			if(target == j){
				faceCheck[j] = faceCheck[j] + 1;
			}
		}

		target = getSuit(individual.hand[i].suit);

		for(j = 0; j <4; j++){
			if (target == j){
				suitCheck[j] = suitCheck[j] + 1;
			}
		}
	}
	/*Now find the numeric value of the hand*/
	result = hand_value(individual, faceCheck, suitCheck);
	
	return result;
}

/*This is the actual computation of the value of the given hand*/

float hand_value(Player ind, char f[], char s[]){
	int i, mark, high, max; 
	int fh, tp, sc; /*ints only for checking*/
	float result;
	result = max = mark = 0;

	/*max is the highest # of matching cards (i.e, one pair would be 2)*/
	/*mark is the # value of the card, Ace = 12, 2 = 0;.*/

	for(i = 0; i<13; i++){
		if (f[i] >= max){
			max = f[i];
			mark = i;
		}
	}

	/*check suit for flush/straight flush/royal flush here*/
	for(i = 0; i<4; i++){
		if (s[i] > 4){
			/*check for type of flush*/
			high = find_high(f);
			sc = straightCheck(f);
			if (sc == 1){
				/*if have a straight and flush, see if ace is involved for royal*/
				if (f[12] == 1 && f[11] == 1){ /*Ace high*/
					return 100 + high; /*royal flush*/
				}
				if (f[12] == 1 && f[0] == 1){
					return 88; /*straight flush Ace low*/
				}

					return 88 + high;/*straight flush*/
				}
			return 63; /*normal Flush*/
		}
	}

	/*check for straight, make function*/

	if (max == 1){
		/*check for straight*/
		sc = straightCheck(f);
		if (sc == 1){
			if (f[12] == 1 && f[0] == 1){
				return 52; /*Ace low straight*/
			}
			high = find_high(f);
			return 50 + high; /*highest card in straight*/
		}

		/*return High Card*/
		return mark;
	}

	if (max == 2){
		/*check for two pair, value is less than three of a kind*/
		tp = twoPairCheck(f);
		if (tp == 1){
			for (i = 12; i > 0; i--){
				if (f[i] == 2){
					mark = i;
					return 26 + mark; /*high value of two pair*/
				}
			}
		}
		return 13 + mark; /*one pair*/
	}

	if (max == 3){
		fh = fullHouseCheck(f);/*check for full house*/
		if (fh == 1){
			return 62 + mark; /*full house*/
		}

		else{	
			return 39 + mark; /*three of a kind*/
		}

	}

	if (max == 4){
		return 75 + mark;/*four of a kind*/
	}

	/*return high card*/
	return mark;

}

int straightCheck(char f []){
	int i, count;
	count = 0;
	for (i = 0; i<12; i++){
		if (f[i] == 1){
			if (f[i+1] == 1){
				count++;
			}
		}
	}
	if (count == 4){
		return 1;
	}
	
	/*special circumstance, ace low*/
	count = 0;
	
	for (i=0; i<4; i++){
		if (f[i] == 1){
			count++;
		}
	}
	if (f[12] == 1){
		count++;
		if (count == 5){
			return 1;
		}
	}

	/*Not a Straight*/
	return 0;
}

/*Check for the full house*/
int fullHouseCheck(char f []){
	int i;
	for (i = 0; i<13; i++){
		if (f[i] == 2){
			return 1;
		}
	}
	return 0;
}

/*check if theres a two pair or single pair*/
int twoPairCheck(char f []){
	int i;
	int check;
	check = 0;
	for (i = 0; i<13; i++){
		if (f[i] == 2){
			check++;
		}
	}

	if (check == 2){
		return 1;
	}

	return 0;
}

/*find highest value card in relation to hand*/
int find_high(char f[]){
	int i, high;
	high = 0;
	for (i = 12; i > 0; i--){
		if (f[i]>0){
			high = i;
			return high;
		}
	}
	return high;
}

/*convert suits to numeric values, Heart = 0, Diamond = 1, Clubs = 2, Spades = 3*/
int getSuit(char numSuit[]){
	if (numSuit[0] == 'H'){
		return 0;
	}
	if (numSuit[0] == 'D'){
		return 1;
	}
	if (numSuit[0] == 'C'){
		return 2;
	}

	return 3;
}

/*convert cards to numeric value, Ace = 12, down to 2 = 0*/
int getNum(char numCard[]){
	int a;
	if (numCard[0] == 'J'){
		return 9;
	}
	if (numCard[0] == 'Q'){
		return 10;
	}
	if (numCard[0] == 'K'){
		return 11;
	}
	if (numCard[0] == 'A'){
		return 12;
	}
	
	a = atoi(numCard);
	return (a - 2);
}
