//
//  main.cpp
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm> // for std::copy

#include "knapsack_app.h"
#include "reader.hpp"

int main(int argc, const char * argv[]) {
    
    Reader reader("../../../data/hard_probs.txt");
    
    //------------
    // KNAPSACK DATA
    
    // below we have 8 sets from the website: http://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/knapsack_01.html
    // which we pass into our DFO
    
    /*
     2 28 // 2 knapsacks, 28 objects
    1898 440 22507 270 14148 3100 4650 30800 615 4975
    1160 4225 510 11880 479 440 490 330 110 560
    24355 2885 11748 4550 750 3720 1950 10500 // 28 weights
    600 600 // 2 knapsack capacities
    45 0 85 150 65 95 30 0 170 0
    40 25 20 0 0 25 0 0 25 0
    165 0 85 0 0 0 0 100 // #1 constr.
    30 20 125 5 80 25 35 73 12 15
    15 40 5 10 10 12 10 9 0 20
    60 40 50 36 49 40 19 150 // #2 constr.
     */

    
    //------------
    // SETUP
    
    int set = 38; // from 1 to 48
    
    //Dfo_knap knap;
    Dfo_knap knap(reader.problems[set-1]);
    
    //------------
    // RUN
    
    // optional arguments: population size + dimensionality reduction factor + dimensions per feature (if reduced):
    // (1) pass in an int and define how many flies to spawn in the swarm (defaults to 50)
    // (2) pass in REDUCED to use dimensionality reduction (not advisable on 8 / defaults to EXTENDED == no reduction)
    // (3) pass in a power of 2 between 1 and 16 to set the number of features to be reducded into 1 dimension
    
    
    //knap.setup(50, EXTENDED);
    knap.setup(50, REDUCED, 4);
    //knap.setup(30, REDUCED)
    //knap.setup();
    
    knap.changeCyclesNum(100001); // set the cycles of the algorithm
    knap.changeAlgo(SWARM_BEST); // set the type of DFO algorithm
    knap.changeGreedVsSafetyRatio(20); // change the ratio between "reward" for filling the knapsack and "punishment" for exceeding the knapsack capacity (it defaults to 10, which makes it practically impossible to exceed the knapsack but doesn't let the algorithm "dare" to fill up)
    knap.changeNeighTopol(DFO::RANDOM);
    
    knap.run();
    
    //------------
    
    return 0;
}
