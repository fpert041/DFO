//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include <stdio.h>
#include "GlobalParam.hpp"

GlobalParam::GlobalParam(){
    // keep leader (best fly) in the equation or not
    democracy = false;
    // dim: the dimensions of the problem
    dim = 10;
    // popSize: the size of the population of 'flys'
    popSize = 20;
    // disturbance threshold
    dt = 0.001;
    // Constant to set the maximum number of Fly Evaluations allowed to the program
    FE_allowed = 300000;
    
    
    bestIndex = -1;
    searchSpaceWidth = std::vector<int>(dim, 100); // the size (range) of each dimension (range => +/-)
    evalCount = 0;
    leftNeighbour = 0;
    rightNeighbour = 0;
    evaluationFunctionName = "";
}
