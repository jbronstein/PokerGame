Student: Josh Bronstein


Game Logic: Every player starts with 100 Galleons. It costs 5 Galleons to play each round, which each player (if they have atleast 5 Galleons) will pay up front. The players are then dealt their hands. The user (who will always go first) can either raise, pass, or fold (since user always goes first, there is never a reason to fold here). Then each computer exchanges their cards based on Monte Carlo advice. The computer has two sets of decisions based on if there has been a raise before their move. If there  has been a raise already, they can either match the raise or fold. If there hasn't been a raise, they can then either raise, pass, or fold. 

After the three computers move, the next situation depends on who raised. If the user is the player who raised, then all computers had a decision whether to match or fold, so we can continue to determine who wins the pot. If the player passed and some computer raised, then we need to ask the user if they want to match, and then whether each computer who hasn't matched, whether they want to match or fold (I use the betMarker to keep track of who placed an original bet/raised each round). The final situation here, is if everyone passed, in that situation, we can just move on to determine the winner.

The winner is the player with the highest hand value based on on my hand_value function (linear based). I only account for a single winner or if there is a two-way tie winner (in which case I split the pot). Then we start a new round.

-------- Specifics -----------

Compile: just run "make" and the makefile should run as expected.

Play Game: game.c is the main file. So ./game should do the trick after compiling.

Structs: I use Card, Deck, and Player structs to achieve my game.

Monte Carlo: My MC_rate is the main function that simulates each of the 32 option exchanges for the player and then recommends the highest value exchange by inserting 1 (Exchange) and 0 (Don't Exchange) into each Player struct's mcAdvice[]. It made sense to me to just keep track of each player's best move as a part of their struct.

Hand Value: For rating hand values, look at my analyze.c file. I first break the hand down into two arrays, one that keeps track of the # of occurrences of each face value, and another to keep track of the # of each suit in the hand. I then send these arrays to the hand_value function to get the actual value. I chose a linear approach. There is no specific linear function involved here, I just looked at hand rankings and made sure none overlapped while including each hand ranking given ace high� It works for all hand types and given the MC recommendations, the hand values work appropriately as you will see. 

Interface Notes/Limitations: I threw in some sleeps throughout this interface so it makes more sense for the user while it runs. Throughout testing this final game, I believe I have caught most of the bugs, but there may still be a couple I may have missed, this would not be too surprising. Also, I have limited error checking so I trust you will typically type in what is expected in the prompt. Finally, my computers are not idiots, but they aren't the brightest bunch. They don't take into account, for example, how much is being bet and how that should compute into whether they match or fold.
