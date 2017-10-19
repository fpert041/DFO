//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include <stdio.h>
#include "GlobalParam.hpp"

// dim: the dimensions of the problem
int GlobalParam::dim = 10;
// popSize: the size of the population of 'flys'
int GlobalParam::popSize = 20;
// disturbance threshold
double GlobalParam::dt = 0.001;
// Constant to set the maximum number of Fly Evaluations allowed to the program
int GlobalParam::FE_allowed = 300000;


int GlobalParam::bestIndex = -1;
int GlobalParam::searchSpaceWidth = 100; // the size (range) of each dimension (range => +/-)
int GlobalParam::evalCount = 0;
int GlobalParam::leftNeighbour = 0;
int GlobalParam::rightNeighbour = 0;
std::string GlobalParam::evaluationFunctionName = "";

std::vector<std::shared_ptr<Fly>> GlobalParam::swarm;



