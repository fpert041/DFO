//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include <stdio.h>
#include "GlobalParam.hpp"

int GlobalParam::bestIndex;
int GlobalParam::searchSpaceWidth;
int GlobalParam::searchSpaceHeight;
int GlobalParam::evalCount;
int GlobalParam::leftNeighbour;
int GlobalParam::rightNeighbour;
std::string GlobalParam::evaluationFunctionName;

std::array<std::shared_ptr<Fly>, GlobalParam::popSize> GlobalParam::swarm;



