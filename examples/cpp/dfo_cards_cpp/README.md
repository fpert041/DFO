# dfo_cards_game
## Applying my cpp DFO to a simple card game problem

You're in a pub in an island and a friend decides to give a million to anyone who could solve the following problem only by using DFO:

Each one of you is given 10 cards, numbered 1-10. You're asked to divide the cards in two groups where the sum of the numbers on the cards in the first group is as close to 36 and the product of the numbers in the second group is as close as possible to 360.

### ASSOCIATED QUESTIONS:
* What is the size of the search space? (i.e. how many possible solutions are there?)
* How would you encode your potential solution vector?
* Some solutions are better than others. Based on this, how would be evaluate your solutions.
* Run DFO for 50 times and report the summary of your results.


### ANSWERS:
* 2 ^ 10  = 1024: You have 10 cards and each can be either in group 1 or 2. This means that card 1 can be either in state 1 or 2, whilst card 2 can be in state 1 or 2 for each state of card 1 (so 2*2 = 2^2). This continues for all the cards, which are 10.
* An array of 10 elements, each of which can take a value between 0 and 1
* We are going to use a fitness function that adds together the card values (array_index+1) in group 0 (array[i] < 0.5 ), then subtracts 36 from such sum, and multiplies it by 10. It then sums the cards in group 1 (array[i] >= 0.5), then subtract 360 from it. It finally adds the two sums together and this value would be a fitness value whose optimal value would be 0. The closer the solutiuon is to 0, the better it is.
* On 10 tests with a population of 80 we got "0" 7 times and "10" 3 times.
