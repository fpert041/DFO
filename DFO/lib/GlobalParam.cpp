//
//  GlobalParam.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

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
    // Parameter for the type of randomness governing the disturbance
    drm = UNI;
    // Parameter for the number of neighbours checked per side
    numNeighbours = 1;
    
    bestIndex = -1;
    searchSpaceWidth = std::vector<int>(dim, 100); // the size (range) of each dimension (can have a range of +/-)
    evalCount = 0;
    leftNeighbour = std::vector<int>(numNeighbours, -1);
    rightNeighbour = std::vector<int>(numNeighbours, -1);
    evaluationFunctionName = "";
}

// ----- setters ----

void GlobalParam::setNumNeighbours(int num){
    // set number of neighbours per side to be checked
    numNeighbours = num;
    leftNeighbour = std::vector<int>(numNeighbours, -1);
    rightNeighbour = std::vector<int>(numNeighbours, -1);
}

void GlobalParam::setDemocracy(bool dem){
    // keep leader (best fly) in the equation or not
    democracy = dem;
}

void GlobalParam::setSearchSpaceWidth(int width){
    searchSpaceWidth = std::vector<int>(dim, width); // the size (range) of each dimension (can have a range of +/-)
    std::cout << "" << std::endl;
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
    FE_allowed = num;
}

void GlobalParam::setDtRandMode(DtRanMode mode){
    // set the type of randomness governing the disturbance
    drm = mode;
}

void GlobalParam::setSwarm(std::vector<std::shared_ptr<Fly>> newS){
    // set the swarm
    if(newS.size() == swarm.size()){
        for(int i = 0; i<newS.size(); i++){
            swarm[i] = newS[i];
        }
    } else
        std::cout << "THE NEW SWARM IS NOT COMPATIBLE" << std::endl;
}


// ----- getters ----

std::vector<std::shared_ptr<Fly>> GlobalParam::getSwarm(){
    return swarm;
}

std::shared_ptr<Fly> GlobalParam::getBestFly(){
    return swarm[bestIndex];
}

bool GlobalParam::getDemocracy(){
    return democracy;
}

std::vector<int> GlobalParam::getSearchSpaceWidth(){
    return searchSpaceWidth;
}

int GlobalParam::getSearchSpaceWidth(int dim){
    return searchSpaceWidth[dim];
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

int GlobalParam::getFEAllowed() {
    return FE_allowed;
}

float GlobalParam::getDt() {
    return float(dt);
}

int GlobalParam::getNumNeighbours() {
    return numNeighbours;
}

std::string GlobalParam::getDtRandMode(){
    // set the type of randomness governing the disturbance
    if(drm == UNI) return "UNIFORM";
    else return "GAUSSIAN";
}


