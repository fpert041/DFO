//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include <stdio.h>
#include "../include/GlobalParam.hpp"

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
    searchSpaceWidth = std::vector<int>(dim, 100); // the size (range) of each dimension (can have a range of +/-)
    evalCount = 0;
    leftNeighbour = 0;
    rightNeighbour = 0;
    evaluationFunctionName = "";
}

// ----- setters ----

void GlobalParam::setDemocracy(bool dem){
    // keep leader (best fly) in the equation or not
    democracy = dem;
}

void GlobalParam::setSearchSpaceWidth(int width){
    searchSpaceWidth = std::vector<int>(dim, width); // the size (range) of each dimension (can have a range of +/-)
}

void GlobalParam::setSearchSpaceWidth(int dim, int width){
    searchSpaceWidth[dim] = width; // the size (range) of each dimension (can have a range of +/-)
}

void GlobalParam::setDim(int dims){
    // dim: the dimensions of the problem
    dim = dims;
}

void GlobalParam::setPopSize(int inPopSize){
    // popSize: the size of the population of 'fliess'
    popSize = inPopSize;
}

void GlobalParam::setDt(double inDt){
    // disturbance threshold
    dt = inDt;
}

void GlobalParam::setFEAllowed(double num){
    // Constant to set the maximum number of Fly Evaluations allowed to the program
    FE_allowed = 300000;
}

// ----- getters ----

bool GlobalParam::getDemocracy(){
    return democracy;
}

std::vector<int> GlobalParam::getSearchSpaceWidth(){
    return searchSpaceWidth;
}

int GlobalParam::getBestIndex(){
    return bestIndex;
}

std::string GlobalParam::getEvalFuncName(){
    return evaluationFunctionName;
}

int GlobalParam::getEvalCount(){
    return evalCount;
}

int GlobalParam::getPopSize(){
    return popSize;
}

int GlobalParam::getDim() {
    return dim;
}


