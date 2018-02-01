//
//  problem.hpp
//  knapsack
//
//  Created by Francesco Perticarari on 03/12/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#ifndef problem_hpp
#define problem_hpp

#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

/*
 EXAMPLE
 This is the WEING1.DAT data file plus some comments, that are NOT
 part of the problem instance!
 
problem WEING1.DAT // Title
 
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

double mean(vector<double>& v);
double stDev(vector<double>& v);

class Problem {
    
public:
    Problem(string name) {probID = name;};
    
    string probID;
    int nKnaps;
    int nObjects;
    int optimalWeight = -1; // OPTIONAL - optimal weight (or profit)
    
    vector<int> weights; // weights (or profits)
    vector<int> capacs;  // capacities (or maximum_carry)
    vector<vector<int>> constraints; // constraints (or weights)
};

#endif /* problem_hpp */
