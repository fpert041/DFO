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

Dfo_knap::Dfo_knap() {};

Dfo_knap::Dfo_knap(int maxCap, std::vector<int> w, std::vector<int> p) {
    knap_capacity = maxCap;
    weights = w;
    profits = p;
};

//------------------------------------------------------------

void Dfo_knap::setup(int popSize, DimensionalReduc r) {
    
    if(r == REDUCED) reduc = true;
    
    numObjects = (int)weights.size();
    int maxWeight = sumVector(weights);
    int maxProfit = sumVector(profits);
    
    // set up a dimensionality
    if(reduc) dfo->setDim(1);
    else dfo->setDim(numObjects);
    
    // set a fitness function that would work for this problem:
    // we need to check whether a card is in group 0 or 1,
    // then we compute and return out a measure of the "error" that we get for each solution
    
    if (reduc) {
        dfo->setFitnessFunc(
                            [this, maxProfit, maxWeight](std::vector<double> p) {
                                int sumWeights = 0;
                                int sumProfit = 0;
                                
                                int N = floor(p[0]); //input number in base 10
                                bitset<64> A=N;//A will hold the binary representation of N
                                
                                for(int i = 0; i<numObjects; ++i) {
                                    if(A[i] >= 0.5) {
                                        sumWeights += weights[i];
                                        sumProfit += profits[i];
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
    } else {
        
        dfo->setFitnessFunc(
                            [this, maxProfit, maxWeight](std::vector<double> p) {
                                int sumWeights = 0;
                                int sumProfit = 0;
                                
                                for(int i = 0; i<numObjects; ++i) {
                                    if(p[i] >= 0.5) {
                                        sumWeights += weights[i];
                                        sumProfit += profits[i];
                                    }
                                }
                                
                                double errW = abs(pow(E, (double)(sumWeights - knap_capacity)/maxWeight)-1.0);
                                //double errW = double(sumWeights - knap_capacity)/maxWeight;
                                if(sumWeights > knap_capacity)
                                errW += 100.0;
                                double errP = double(maxProfit - sumProfit)/maxProfit;
                                double fitness = errW + errP*10;
                                
                                return fitness;
                                
                            }
                            );
    }

    
    
    // set up a populatin size of 100
    dfo->setPopSize(popSize);
    
    // set the range of all the dimensions of the search space
    if (reduc)  dfo->setSearchSpaceWidth(pow(2,numObjects));
    else dfo->setSearchSpaceWidth(1);
    
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

void Dfo_knap::run() {

    // run the algorithm 100 times
    for (int i = 0; i<dfo->getFEAllowed(); ++i){
        dfo->updateSwarm();
        
        if(i%1000 == 0) {
            
            float fitness = dfo->getBestFly()->getFitness();
            std::cout << "cycle: " << i << std::endl;
            std::cout << "best fly index: " << dfo->getBestIndex() << std::endl;
            
            if(reduc) {
                int N = int(dfo->getBestFly()->getPos(0)); //input number in base 10
                bitset<64> A=N;//A will hold the binary representation of N
                std::cout << "best fly location: " << dfo->getBestFly()->getPos(0) << std::endl;
                for (int i = 0; i<numObjects; i++) std::cout << A[i] << " ";
                std::cout << std::endl;
            } else {
                std::vector<double> bestPos = dfo->getBestFly()->getPos();
                for(int i = 0; i<bestPos.size(); ++i){
                    if(bestPos[i] < 0.5)
                    bestPos[i] = 0;
                    else
                    bestPos[i] = 1;
                }
                std::cout << "best fly location: " << vect_to_string(bestPos) << std::endl;
            }
            std::cout << "fitness: "<< fitness << std::endl;
            
            if (fitness == 0) {
                std::cout << "iterations needed: "<< i << std::endl;
                std::cout << "---" << std::endl;
                break;
            }
            std::cout << "---" << std::endl;
        }
    }
}
