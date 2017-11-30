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
    
    Reader reader;
    
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
    
    std::array<int, 8> knap_capacityA = {165, 26, 190, 50, 104, 170, 750, 6404180};
    std::array<std::vector<int>, 8> weightsA ={
        std::vector<int> {23,31,29,44,53,38,63,85,89,82},
        std::vector<int> { 12, 7, 11, 8, 9},
        std::vector<int> {56, 59, 80, 64, 75, 17},
        std::vector<int> {31,10, 20,19,4,3,6},
        std::vector<int> {25,35,45,5,25,3,2,2},
        std::vector<int> {41,50,49,59,55,57,60},
        std::vector<int> {70,73,77,80,82,87,90,94,98,106,110,113,115,118,120},
        std::vector<int> {382745, 799601, 909247, 729069,
            467902, 44328, 34610, 698150, 823460, 903959, 853665, 551830, 610856, 670702 , 488960,
            951111, 323046, 446298, 931161, 31385, 496951, 264724, 224916, 169684},
    };
    std::array<std::vector<int>, 8> profitsA = {
        std::vector<int> {92,57,49,68,60,43,67,84,87,72},
        std::vector<int> {24,13,23,15,16},
        std::vector<int> {50,50,64,46,50,5},
        std::vector<int> {70,20,39,37,7,5,10},
        std::vector<int> {350,400,450,20,70,8,5,5},
        std::vector<int> {442,525,511,593,546,564,617},
        std::vector<int> {135,139,149,150,156,163,173,184,192,201,210,214,221,229,240},
        std::vector<int> {825594, 1677009, 1676628, 1523970, 943972, 97426, 69666, 1296457, 1679693, 1902996, 1844992, 1049289, 1252836, 1319836, 953277, 2067538, 675367, 853655, 1826027, 65731, 901489, 577243, 466257, 369261},
    };

    vector<int> knap_capacityZ = {600, 600};
    
    std::vector<int> weightsZ { 1898, 440, 22507, 270, 14148, 3100, 4650, 30800, 615, 4975,
        1160, 4225, 510, 11880, 479, 440, 490, 330, 110, 560,
        24355, 2885, 11748, 4550, 750, 3720, 1950, 10500};

    vector<vector<int>> constrZ {
        { 45, 0, 85, 150, 65, 95, 30, 0, 170, 0, 40, 25, 20, 0, 0, 25, 0, 0, 25, 0, 165, 0, 85, 0, 0, 0, 0, 100},
        { 30, 20, 125, 5, 80, 25, 35, 73, 12, 15, 15, 40, 5, 10,10, 12, 10, 9, 0, 20, 60, 40, 50, 36, 49, 40, 19, 150}
    };
    
    ///// Solutions /////
    //1 1 1 1 0 1 0 0 0 0
    //0 1 1 1 0
    //1 1 0 0 1 0
    //1 0 0 1 0 0 0
    //1 0 1 1 1 0 1 1
    //0 1 0 1 0 0 1
    //1 0 1 0 1 0 1 1 1 0 0 0 0 1 1
    //1 1 0 1 1 1 0 0 0 1 1 0 1 0 0 1 0 0 0 0 0 1 1 1
    
    //------------
    // SETUP
    
    //int set = 7; // from 1 to 8
    
    //Dfo_knap knap;
    Dfo_knap knap(knap_capacityZ, weightsZ, constrZ);
    
    //------------
    // RUN
    
    // arguments: population size & dimensionality reduction factor:
    // (1) pass in an int and define how many flys to spawn in the swarm (defaults to 50 but problems 1 - 7 can easily be tackled with 10 or 20)
    // (2) pass in REDUCED to use dimensionality reduction (not advisable on 8 / defaults to EXTENDED == no reduction)
    //knap.setup(10, REDUCED);
    knap.setup(30);
    
    knap.changeCyclesNum(50001);
    
    knap.run();
    
    //------------
    
    return 0;
}
