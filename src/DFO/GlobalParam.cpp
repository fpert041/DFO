//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include <stdio.h>
#include "GlobalParam.hpp"

int GlobalParam::bestIndex = -1;
int GlobalParam::searchSpaceWidth = GlobalParam::dim*10;
int GlobalParam::searchSpaceHeight = searchSpaceWidth+GlobalParam::dim;
int GlobalParam::evalCount = 0;
int GlobalParam::leftNeighbour = 0;
int GlobalParam::rightNeighbour = 0;
std::string GlobalParam::evaluationFunctionName = "";

std::array<std::shared_ptr<Fly>, GlobalParam::popSize> GlobalParam::swarm;



