//
//  Fly.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 10/10/2017.
//

#include "../include/Fly.hpp"


Fly::Fly(std::vector<double> inPos, GlobalParam& context){ // CONSTRUCTOR
    pos = inPos; // set the position of the fly
    exPos = pos; // initially the old position vector is initialised using the same values as the actual position vector
    posDimensions = inPos.size(); // set the value that holds the number of dimensions of the space where the fly lives
    pContext = &context; // track the swarm we are in
}

Fly::Fly(std::vector<double> inPos, GlobalParam* p_context){ // CONSTRUCTOR_2
    pos = inPos; // set the position of the fly
    exPos = pos; // initially the old position vector is initialised using the same values as the actual position vector
    posDimensions = inPos.size(); // set the value that holds the number of dimensions of the space where the fly lives
    pContext = p_context; // track the swarm we are in
}


Fly::~Fly(){ // DESTRUCTOR
//    delete pRightNeighbour;
//    delete pLeftNeighbour;
    pLeftNeighbour = nullptr;
    pRightNeighbour = nullptr;
}

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

const std::vector<double>& Fly::getPos(){ // get the vector ("of coordinates") of the fly's position (in the search space)
    return pos;
}

//------------------------------------------------------------------------------------

const double Fly::getPos(int n) { //overloaded function to get the value of a single dimension from the fly's position
    return pos[n];
}

//------------------------------------------------------------------------------------

const std::vector<double> Fly::getExPos() { // get the vector of the previous position ("coordinates")
    return exPos;
}

//------------------------------------------------------------------------------------

const double Fly::getExPos(int n) { // get the value of dimension "n" in the previous position ("coordinates")
    return exPos[n];
}

//------------------------------------------------------------------------------------

void Fly::setPos(std::vector<double> position) { // set the position of the fly with a vector supplied as argument
    if( !(position.size() == pos.size()) ){
        std::cout << "Vector supplied is not the same size as the current fly's dimension" << std::endl;
        return void();
    }
    exPos = pos;
    pos = position;
}

//------------------------------------------------------------------------------------

void Fly::setPos(int n, double inPos) { // change one specific dimension (n) of the fly's position to 'inPos'
    exPos[n] = pos[n];
    pos[n] = inPos;
}

//------------------------------------------------------------------------------------

void Fly::setFitness(double t) { // set fitness value
    fitness = t;
}

//------------------------------------------------------------------------------------


const double Fly::getFitness() { // return fitness value
    return fitness;
}

//------------------------------------------------------------------------------------

const double Fly::getDistance(int n) { // euclidean distance between position vectors
    double squaredSum = 0;
    for (int d = 0; d < posDimensions - 1; d++) {
        squaredSum += std::pow(getPos(d) - pContext->swarm[n]->getPos(d), 2);
    }
    return std::sqrt(squaredSum);
}

//------------------------------------------------------------------------------------

const std::string Fly::toString() { // return the vector of the fly's coordinate as a string
    std::string s = "";
    for (int d = 0; d < posDimensions; ++d )
        s.append(std::to_string(pos[d]) ).append(", ");
    return s;
}

