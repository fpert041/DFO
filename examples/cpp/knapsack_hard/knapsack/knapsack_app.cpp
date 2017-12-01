//
//  dfo_game.cpp
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//


#include "knapsack_app.h"
using namespace dfoHelpers;

//------------------------------------------------------------

//Dfo_knap::Dfo_knap() {};

Dfo_knap::Dfo_knap(vector<int>maxCap, vector<int> w, vector<vector<int>> c) {
    knap_capacity = maxCap;
    numKnaps = int(maxCap.size());
    weights = w;
    constraints = c;
};

//------------------------------------------------------------

void Dfo_knap::setup(int popSize, DimensionalReduc r) {
    
    // check if a REDUCED flag has been passed in as 2n arg (if so turn bool switch)
    if(r == REDUCED) reduc = true;
    
    // check and store the number of given objects
    numObjects = (int)weights.size();
    
    // compute and store the maximum weight (profit) that would be possible if all objects could be taken on
    maxWeight = sumVector(weights);
    
    // compute and store the max contraints (volume/"bad weight") that all objects would have IN EACH knapsack
    // If the knapsack had infinite capacity
    maxConsts = vector<int>(numKnaps, 0);
    for(int i = 0; i<constraints.size();  ++i){
        maxConsts[i] = sumVector(constraints[i]);
    }
    
    // set up a dimensionality
    //if(false/*reduc*/) dfo->setDim(1);
    //else
        dfo->setDim(numObjects);
    
    // set a fitness function that would work for this problem:
    // we need to check whether a card is in group 0 or 1,
    // then we compute and return out a measure of the "error" that we get for each solution
    if (false/*reduc*/) {
        /*
        dfo->setFitnessFunc(
                            [this, maxConsts, maxWeight](std::vector<double> p) {
                                int sumWeights = 0;
                                int sumConstr = 0;
                                
                                int N = floor(p[0]); //input number in base 10
                                bitset<64> A=N;//A will hold the binary representation of N
                                
                                for(int i = 0; i<numObjects; ++i) {
                                    if(A[i] >= 0.5) {
                                        sumWeights += weights[i];
                                        sumConstr += constraints[i][i];
                                    }
                                }
                                
                                double errW = abs(pow(E, (double)(sumWeights - knap_capacity)/maxWeight)-1.0);
                                //double errW = double(sumWeights - knap_capacity)/maxWeight;
                                if(sumWeights > knap_capacity)
                                errW += 100.0;
                                double errP = double(maxProfit - sumProfit)/maxProfit;
                                double fitness = errW + errP*10;
                                if (N<0) fitness += 100.0;
                                
                                return fitness;
                                
                            }
                            );
         */
        dfo->resetFitnessFunc();
    } else {
        
        dfo->setFitnessFunc(
                            [this](std::vector<double> p) {
                                int sumWeights = 0;
                                vector<int> sumConst = vector<int>(numKnaps, 0);
                                
                                for(int i = 0; i<numObjects; ++i) {
                                    if((p[i] >= 0.5)){ /*&& p[i] < knap_capacity.size())) { // ** distributed rack */
                                        sumWeights += weights[i];
                                        for(int j = 0; j<numKnaps; ++j){
                                            sumConst[j] += constraints[j][i];
                                        }
                                        //int knapSelect = floor(p[i]+0.5)-1; // ** distributed rack
                                        //sumConst[knapSelect] += constraints[knapSelect][i];
                                        //sumConst
                                    }
                                }

                                double errC = 0;
                                for(int i = 0; i<numKnaps; ++i){
                                    //errC += abs(pow(E, (double)(sumConst[i] - knap_capacity[i])/maxConsts[i])-1.0);
                                    if(sumConst[i] > knap_capacity[i]) errC += 100.0;
                                }
                                errC /= numKnaps;
                                
                                double errW = double(maxWeight - sumWeights)/maxWeight;
                                
                                double fitness = errC + errW;
                                
                                return fitness;
                                
                            }
                            );
    }

    
    
    // set up a populatin size of 100
    dfo->setPopSize(popSize);
    
    // set the range of all the dimensions of the search space
    //if (false/*reduc*/)  //dfo->setSearchSpaceWidth(pow(2,numObjects));
    //else dfo->setSearchSpaceWidth(int(constraints.size())); // distributed racksack
    //else
        dfo->setSearchSpaceWidth(1);
    
    // set neighbour-best algorithm rather swarm-best version (which would be prone to fall into local minima)
    dfo->setDemocracy(true);
    
    // increase the likelyhood of a random dispersion
    dfo->setDt(0.1);
    
    // constarin each dimension to a range between 0 and 1
    dfo->setConstrainPos(true);
    
    // set security stopper for maximum
    dfo->setFEAllowed(50001);

    
    //---------------------------
    
    // generate the swarm so that it starts off only on the positive hyperoctant of our search space
    /* Note --  In geometry, an orthant or hyperoctant is the analogue in n-dimensional Euclidean space of a quadrant in the plane or an octant in three dimensions.
     */
    dfo->generateSwarmPositiveAxis();
    
    

}

void Dfo_knap::changeCyclesNum(int newNum){
    dfo->setFEAllowed(newNum);
}

void Dfo_knap::run() {

    // run the algorithm 100 times
    for (int i = 0; i<dfo->getFEAllowed(); ++i){
        dfo->updateSwarm();
        
        if(i%1000 == 0) {
            
            float fitness = dfo->getBestFly()->getFitness();
            int bestMaxWeight = 0;
            vector<int> testCons = vector<int>(numKnaps, 0);
            int testCons2 = 0;
            std::cout << "cycle: " << i << std::endl;
            std::cout << "best fly index: " << dfo->getBestIndex() << std::endl;
            
            if(/*reduc*/false) {
                int N = int(dfo->getBestFly()->getPos(0)); //input number in base 10
                bitset<64> A=N;//A will hold the binary representation of N
                std::cout << "best fly location: " << dfo->getBestFly()->getPos(0) << std::endl;
                for (int i = 0; i<numObjects; i++) std::cout << A[i] << " ";
                std::cout << std::endl;
            } else {
                std::vector<double> bestPos = dfo->getBestFly()->getPos();
                for(int i = 0; i<bestPos.size(); ++i){
                    bestPos[i] = floor(bestPos[i] + 0.5);
                    if(bestPos[i] >= 0.5){
                        bestMaxWeight += weights[i];
                        for(int j = 0; j<numKnaps; ++j){
                            testCons[j] += constraints[j][i];
                        }
                    }
                }
                std::cout << "best fly location: " << vect_to_string(bestPos) << std::endl;
            }
            std::cout << "fitness: "<< fitness << std::endl;
            std::cout << "best weight obtained : "<< bestMaxWeight << std::endl;
            
            std::cout << "best fly's used capacities:"<< std::endl;
            for(int i = 0; i<numKnaps; ++i){
                std::cout << "knap " << i+1 << ": " << testCons[i] << " ";
            }
            std::cout << std::endl;
            
            if (fitness == 0) {
                std::cout << "iterations needed: "<< i << std::endl;
                std::cout << "---" << std::endl;
                break;
            }
            std::cout << "---" << std::endl;
        }
    }
}
