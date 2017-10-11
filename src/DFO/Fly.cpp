//
//  Fly.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 10/10/2017.
//

#include "Fly.hpp"


Fly::~Fly(){
    delete pRightNeighbour;
    delete pLeftNeighbour;
    pLeftNeighbour = nullptr;
    pRightNeighbour = nullptr;
}

