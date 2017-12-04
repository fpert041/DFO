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

Dfo_knap::Dfo_knap() {
    numKnaps = 2;
    numObjects = 28;
    knap_capacity = {600, 600};
    weights = { 1898, 440, 22507, 270, 14148, 3100, 4650, 30800, 615, 4975,
        1160, 4225, 510, 11880, 479, 440, 490, 330, 110, 560,
        24355, 2885, 11748, 4550, 750, 3720, 1950, 10500};
    constraints = {
        { 45, 0, 85, 150, 65, 95, 30, 0, 170, 0, 40, 25, 20, 0, 0, 25, 0, 0, 25, 0, 165, 0, 85, 0, 0, 0, 0, 100},
        { 30, 20, 125, 5, 80, 25, 35, 73, 12, 15, 15, 40, 5, 10,10, 12, 10, 9, 0, 20, 60, 40, 50, 36, 49, 40, 19, 150}};
    optimalWight = 141278;
}

Dfo_knap::Dfo_knap(Problem& data){
    pProblemData = &data;
    optimalWight = data.optimalWeight;
    constraints = data.constraints;
    weights = data.weights;
    knap_capacity = data.capacs;
    numObjects = data.nObjects;
    numKnaps = data.nKnaps;
}

Dfo_knap::Dfo_knap(Problem* data){
    pProblemData = data;
    optimalWight = data->optimalWeight;
    constraints = data->constraints;
    weights = data->weights;
    knap_capacity = data->capacs;
    numObjects = data->nObjects;
    numKnaps = data->nKnaps;
}

Dfo_knap::Dfo_knap(vector<int>maxCap, vector<int> w, vector<vector<int>> c, int targetOptimum) {
    knap_capacity = maxCap;
    numKnaps = int(maxCap.size());
    weights = w;
    constraints = c;
    optimalWight = targetOptimum;
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
    if(reduc) {
        chunks = ceil(float(numObjects)/dimsPerFeature);
        dfo->setDim(chunks);
    }
    else
        dfo->setDim(numObjects);
    
    // set the range of all the dimensions of the search space (it's important that this comes AFTER the setting of the dimension number)
    if (reduc)  {
        newFtSize = pow(2,dimsPerFeature)-1;
        dfo->setSearchSpaceWidth(newFtSize);
        int lastChunkDim = numObjects%dimsPerFeature;
        dfo->setSearchSpaceWidth(chunks-1, pow(2, lastChunkDim)-1);
    } else
        dfo->setSearchSpaceWidth(1);
    
    // set a fitness function that would work for this problem:
    // we need to check whether a card is in group 0 or 1,
    // then we compute and return out a measure of the "error" that we get for each solution
    if (reduc) {
        
        dfo->setFitnessFunc(
                            [this](std::vector<double> p) {
                                int sumWeights = 0;
                                vector<int> sumConst = vector<int>(numKnaps, 0);
                                
                                for(int k = 0; k<chunks; ++k){
                                    int N = floor(p[k]+0.5); //input number in base 10
                                    bitset<16> A=N; //A will hold the binary representation of N up to 16 bits (we don't really need anything bigger than this as the dimensions should be constrained to lower values anyway)
                                    
                                    for(int i = 0; i<dimsPerFeature; ++i) {
                                        if(A[i] >= 0.5) {
                                            sumWeights += weights[i+k*dimsPerFeature];
                                            for(int j = 0; j<numKnaps; ++j){
                                                sumConst[j] += constraints[j][i+k*dimsPerFeature];
                                            }
                                        }
                                    }
                                }
                                
                                double errC = 0;
                                for(int i = 0; i<numKnaps; ++i){
                                    if(sumConst[i] > knap_capacity[i]) errC += 100.0;
                                }
                                errC /= numKnaps;
                                
                                double errW = double(maxWeight - sumWeights)/maxWeight;
                                
                                double fitness = errC + errW;
                                
                                //if (N<0) fitness += 100.0; // Only useful if I don't constrain the swarm (which I do)
                                //if (N>pow(2,numObjects)) fitness += 100.0 // ''
                                
                                return fitness;
                            }
                            );
         
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
    
    // set neighbour-best algorithm rather swarm-best version (which would be prone to fall into local minima)
    dfo->setDemocracy(true);
    
    // increase the likelyhood of a random dispersion
    dfo->setDt(0.2);
    
    // constarin each dimension to a range between 0 and 1
    dfo->setConstrainPos(true);
    
    // set security stopper for maximum
    dfo->setFEAllowed(50001);
    
    // set type of randomness for disturbance
    //dfo->setDtRandMode(DFO::GAUSS); // Seems to be better without this
    
    // set type of neighbouring topology
    //dfo->setNeighbourTopology(DFO::RANDOM); // Seems to be better without this
    
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
        std::vector<double> bestPos = dfo->getBestFly()->getPos();
        if(i%1000 == 0) {
            
            float fitness = dfo->getBestFly()->getFitness();
            int bestMaxWeight = 0;
            vector<int> testCons = vector<int>(numKnaps, 0);
            std::cout << "cycle: " << i <<  "\n";
            std::cout << "pop. size: " << dfo->getPopSize() << ", ";
            std::cout << "nghbr topol. used: " << dfo->getNeighbourTopology() << ", ";
            std::cout << "DT type: " << dfo->getDtRandMode() << "\n";
            std::cout << "best fly index: " << dfo->getBestIndex() <<  "\n";
            
            if(reduc) {
                std::cout << "best fly location: " ;
                for(int j = 0; j<chunks; ++j){
                    int N = floor(bestPos[j]+0.5); //input number in base 10
                    bitset<16> A=N;//A will hold the binary representation of N with 16 bits precision
                    for (int i = 0; i<dimsPerFeature; ++i){
                        std::cout << A[i] << " ";
                        if(A[i] >= 0.5) {
                            bestMaxWeight += weights[i+j*dimsPerFeature];
                            for(int j = 0; j<numKnaps; ++j){
                                testCons[j] += constraints[j][i+j*dimsPerFeature];
                            }
                        }
                    }
                    cout << "(" << dfo->getBestFly()->getPos(j) << ") ";
                    //cout << "| ";
                }
                std::cout <<  "\n";
            } else {
                for(int i = 0; i<bestPos.size(); ++i){
                    bestPos[i] = floor(bestPos[i] + 0.5);
                    if(bestPos[i] >= 0.5){
                        bestMaxWeight += weights[i];
                        for(int j = 0; j<numKnaps; ++j){
                            testCons[j] += constraints[j][i];
                        }
                    }
                }
                std::cout << "best fly location: " << vect_to_string(bestPos) <<  "\n";
            }
            std::cout << "fitness: "<< fitness <<  "\n";
            std::cout << "best fly's suggested fill-ups:"<<  "\n";
            for(int i = 0; i<numKnaps; ++i){
                std::cout << "knap " << i+1 << ": " << testCons[i] << " ";
            }
            std::cout <<  "\n";
            std::cout << "best weight obtained : "<< bestMaxWeight <<  "\n";
            std::cout << "best weight target : "<< optimalWight <<  "\n";
            
            if (bestMaxWeight == optimalWight) {
                std::cout << "iterations needed: "<< i <<  "\n";
                std::cout << "---" << std::endl;
                break;
            }
            std::cout << "---" << std::endl;
        }
    }
}
