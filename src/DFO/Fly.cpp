//
//  Fly.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 10/10/2017.
//

#include "Fly.hpp"


Fly::Fly(std::vector<double> inPos){ // CONSTRUCTOR
    pos = inPos; // set the position of the fly
    posDimensions = inPos.size(); // set the value that holds the number of dimensions of the space where the fly lives
}


Fly::~Fly(){ // DESTRUCTOR
//    delete pRightNeighbour;
//    delete pLeftNeighbour;
    pLeftNeighbour = nullptr;
    pRightNeighbour = nullptr;
}


const std::vector<double> Fly::getPos(){ // get the vector ("of coordinates") of the fly's position (in the search space)
    return pos;
}

const double Fly::getDistance(int n) {
    double squaredSum = 0;
    for (int d = 0; d < posDimensions - 1; d++) {
        squaredSum = squaredSum + std::pow(getPos(d) - GlobalParam::swarm[n]->getPos(d), 2);
    }
    return std::sqrt(squaredSum);
}
