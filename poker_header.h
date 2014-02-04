#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>

#define HAND 5
#define DSIZE 52
#define PLAYERS 4

typedef struct card{
	char *face;
	char *suit;
} Card;

typedef struct deck{
	Card stack[DSIZE];/*I call 52 cards a stack*/
} Deck;

typedef struct player{
	char *name;
	Card hand[HAND];
	int mcAdvice[HAND]; /*This is a 5 int array of 1's and 0's telling computer/user which cards to exchange*/
	double galleons; /*Amount of money each player has*/
	double checkBet; /*bet amount if this player is the better, only one better per game, everyone else matches or folds*/
	int inGame; /*1 if in game, 0 if not*/
} Player;

void setup(Player * nPlayer, char * uName);
void fillDeck(Deck * wDeck); /* char * wFace[], char * wSuit[]);*/
void shuffleDeck(Deck * wDeck);
void shuffleDeckMC(Deck * wDeck);
void dealOut(Deck * wDeck, Player * totalPlayers);
void dequeue(Deck * wDeck);
void exchangeCards(Player * nPlayer, Deck * wDeck);
void displayHand(Player * nPlayer);
float analyze_hand(Player);
int getNum(char num[]);
int getSuit(char numSuit[]);
float hand_value(Player nPlayer, char f[], char s[]);
int find_high(char f[]);
int fullHouseCheck(char f[]);
int twoPairCheck(char f[]);
int straightCheck(char f[]);
Deck MC_sim_deck(Player * nPlayer, int numPlayer);
float MC_rate(Player * nPlayer, int numPlayer);
void advice(Player * nPlayer);
void computerExchange(Player * nPlayer, Deck * wDeck, int numPlayer);
void comp_decision(Player * nPlayer, int numPlayer, double * uBet, double * pot);
void endPlayer(Player * nPlayer, int numPlayer);
void findWinner(Player * nPlayer, double * pot);
double placeBet(Player * nPlayer, double * total);
