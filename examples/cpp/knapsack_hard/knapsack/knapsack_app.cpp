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
    probID = "Example Problem";
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
    counter2 = 0;
}

Dfo_knap::Dfo_knap(Problem& data){
    pProblemData = &data;
    probID = data.probID;
    optimalWight = data.optimalWeight;
    constraints = data.constraints;
    weights = data.weights;
    knap_capacity = data.capacs;
    numObjects = data.nObjects;
    numKnaps = data.nKnaps;
    counter2 = 0;
}

Dfo_knap::Dfo_knap(Problem* data){
    pProblemData = data;
    probID = data->probID;
    optimalWight = data->optimalWeight;
    constraints = data->constraints;
    weights = data->weights;
    knap_capacity = data->capacs;
    numObjects = data->nObjects;
    numKnaps = data->nKnaps;
    counter2 = 0;
}

Dfo_knap::Dfo_knap(vector<int>maxCap, vector<int> w, vector<vector<int>> c, int targetOptimum) {
    knap_capacity = maxCap;
    numKnaps = int(maxCap.size());
    weights = w;
    constraints = c;
    optimalWight = targetOptimum;
};

//------------------------------------------------------------

void Dfo_knap::setup(int popSize, DimensionalReduc r, int ftPerDim) {
    
    // check if a REDUCED flag has been passed in as 2n arg (if so turn bool switch)
    if(r == REDUCED) reduc = true;
    
    if(ftPerDim!=1 && ftPerDim!=2 && ftPerDim!=4 && ftPerDim!=8 && ftPerDim!=16){
        throw myex;
        return;
    }
    dimsPerFeature = ftPerDim;
    
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
        lastChunkDim = numObjects%dimsPerFeature;
        // Conditional Operator = condition ? result_if_true : result_if_false
        lastChunkDim = (lastChunkDim==0) ? dimsPerFeature : lastChunkDim;
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
                                bitset<16> A;//A will hold the binary representation of N up to 16 bits (we don't really need anything bigger than this as the dimensions should be constrained to lower values anyway)
                                for(int k = 0; k<chunks-1; ++k){
                                    int N = floor(p[k]+0.5); //input number in base 10
                                    A=N;
                                    for(int i = 0; i<dimsPerFeature; ++i) {
                                        if(A[i] >= 0.5) {
                                            sumWeights += weights[i+k*dimsPerFeature];
                                            for(int j = 0; j<numKnaps; ++j){
                                                sumConst[j] += constraints[j][i+k*dimsPerFeature];
                                            }
                                        }
                                    }
                                    A=0;
                                }
                                
                                // last chunk ---
                                int N = floor(p[chunks-1]+0.5); //input number in base 10
                                A=N;
                                for(int i = 0; i<lastChunkDim; ++i) {
                                    if(A[i] >= 0.5) {
                                        sumWeights += weights[i+(chunks-1)*dimsPerFeature];
                                        for(int j = 0; j<numKnaps; ++j){
                                            sumConst[j] += constraints[j][i+(chunks-1)*dimsPerFeature];
                                        }
                                    }
                                }
                                A=0;
                                //----
                                
                                double errC = 0;
                                for(int i = 0; i<numKnaps; ++i){
                                    if(sumConst[i] > knap_capacity[i]) errC += 1.0;
                                }
                                errC /= numKnaps;
                                
                                double errW = double(maxWeight - sumWeights)/maxWeight;
                                
                                double fitness = errC*weightVsConstRatio + errW;
                                
                                //if (N<0) fitness += 100.0; // Only useful if I don't constrain the swarm (which I do)
                                //if (N>pow(2,numObjects)) fitness += 100.0 // ''
                                
                                return fitness*10.;
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
                                
                                double fitness = errC*weightVsConstRatio + errW;
                                
                                return fitness*10.;
                                
                            }
                            );
    }
    
    
    // set neighbours to check per side
    dfo->setNumNeighbours(4);
    
    // set up a populatin size of 100
    dfo->setPopSize(popSize);
    
    // set neighbour-best algorithm rather swarm-best version (which would be prone to fall into local minima)
    dfo->setDemocracy(demo);
    
    // increase the likelyhood of a random dispersion
    dfo->setDt(0.1);
    
    // constarin each dimension to a range between 0 and 1
    dfo->setConstrainPos(true);
    
    // set security stopper for maximum
    dfo->setFEAllowed(FEAllowed);
    
    // set type of randomness for disturbance
    //dfo->setDtRandMode(DFO::GAUSS); // Seems to be better without this (not sure when reducing features)
    
    // set type of neighbouring topology
    //dfo->setNeighbourTopology(DFO::RANDOM); // Seems to be better without this
    
    //---------------------------
    
    // generate the swarm so that it starts off only on the positive hyperoctant of our search space
    /* Note --  In geometry, an orthant or hyperoctant is the analogue in n-dimensional Euclidean space of a quadrant in the plane or an octant in three dimensions.
     */
    dfo->generateSwarmPositiveAxis();
    
}

void Dfo_knap::changeCyclesNum(int newNum){
    FEAllowed = newNum;
    dfo->setFEAllowed(newNum);
}

void Dfo_knap::changeAlgo(AlgoType type){
    demo = type;
    dfo->setDemocracy(type);
}

void Dfo_knap::changeGreedVsSafetyRatio(float ratio){
    weightVsConstRatio = ratio;
};

void Dfo_knap::changeNeighTopol(DFO::NeighbouringTopologyType ntt){
    dfo->setNeighbourTopology(ntt);
};

void Dfo_knap::run() {
    float targetWvsC = weightVsConstRatio;
    float newDt = 0.8;
    float targetDt = dfo->getDt();
    int counter = 0;
    int i = 0;
    vector<int> testCons = vector<int>(numKnaps, 0);
    
    int tenPercentFEA = floor(dfo->getFEAllowed()*0.2);
    
    std::vector<double> bestPos = dfo->getBestFly()->getPos();
    int bestMaxWeight = 0;
    
    // run the algorithm N% of allowed times (useful for partially taking advantage of dimensionality reduction)
    for (i = 0; i<tenPercentFEA; ++i){
        
        adapt(newDt, targetDt, counter, targetWvsC, bestMaxWeight, bestPos, testCons);
        
        // analysis
        if(i%1000 == 0) {
            report(i, bestPos, bestMaxWeight, testCons);
        }
        if (bestMaxWeight == optimalWight) {
            std::cout <<  "\n";
            std::cout << "best weight obtained : "<< bestMaxWeight <<  "\n";
            std::cout << "best weight target : "<< optimalWight <<  "\n";
            std::cout << "iterations needed: "<< i <<  "\n";
            std::cout << "---" << std::endl;
            break;
        }
    }
    
    // spread out the dimensions:
    // If the algorithm has taken advantage of dimensionality reduction "speed-up", now it's time to investigate dimensions individually!
    
    bestPos = dfo->getBestFly()->getPos(); // save the best fly's position
    std::vector<double> binaryBestPos(numObjects, 0); // create a vector of doubles to hold its binary equivalent
    
    // convert current best fly's position into a binary sequence
    bitset<16> A;//A will hold the binary representation of N with 16 bits precision
    for(int k = 0; k<chunks-1; ++k){
        int N = floor(bestPos[k]+0.5); //input number in base 10
        A=N;
        for (int i = 0; i<dimsPerFeature; ++i){
            binaryBestPos[k*dimsPerFeature+i] = A[i];
        }
        A=0;
    }
    // last chunk of the binary sequence ---
    int N = floor(bestPos[chunks-1]+0.5); //input number in base 10
    A=N;
    for (int i = 0; i<lastChunkDim; ++i){
        binaryBestPos[(chunks-1)*dimsPerFeature+i] = A[i];
    }
    A=0;
    
    //release memory holding the swarm
    dfo.release();
    // switch dimensionality reduction off (if it's on)
    reduc = false;
    
    // re-spwan a new swarm
    dfo.reset(new DFO());
    // re-set it up with the current characteristics
    setup();
    // pass best position onwards as a leader
    dfo->setLeader(binaryBestPos);
    
    // run the algorithm until the max number of flies evaluations allowed
    for (i = tenPercentFEA; i<dfo->getFEAllowed(); ++i){
    
        adapt(newDt, targetDt, counter, targetWvsC, bestMaxWeight, bestPos, testCons);
        
        // analysis
        if(i%1000 == 0) {
            report(i, bestPos, bestMaxWeight, testCons);
        }
        if (bestMaxWeight == optimalWight) {
            std::cout <<  "\n";
            std::cout << "best weight obtained : "<< bestMaxWeight <<  "\n";
            std::cout << "best weight target : "<< optimalWight <<  "\n";
            std::cout << "iterations needed: "<< i <<  "\n";
            std::cout << "---" << std::endl;
            break;
        }
    }
    
}


// Function for calling the update method of the algorithm, testing features, and a modify a few parameters if it gets stuck

void Dfo_knap::adapt(float& newDt, float& targetDt, int& counter, float& wvsc, int& bestMaxWeight, vector<double>& bestPos, vector<int> testCons){
    bestMaxWeight = 0;
    
    newDt = (newDt >= targetDt) ? targetDt : (newDt - 0.001);
    dfo->setDt(newDt);
    dfo->updateSwarm();
    
    double tempfitness = dfo->getBestFly()->getFitness();
    if(tempfitness == fitness){
        counter ++;
    } else {
        counter = floor(counter*0.1);
        weightVsConstRatio = weightVsConstRatio >= wvsc*2 ? wvsc*2 : weightVsConstRatio + 0.02;
    }
    
    // IMPORTANT WOW! FACTOR: THIS PART CHANGES DYNAMICALLY HOW THE ALGORITHM WORKS AND HOW THE FITNESS FUNCTION ASSESSES THE FITNESS REWARDS/PENALTIES --> In case the algorithm gets stuck, the equations are pushed "outside of the allowed parameters to explore the search space through "non acdeptable paths". This means that the fitness function starts to temporarily give less "penalty" to knapsacks that are filled above their limit. This allows the algorithm to "explore" more when it remains blocked for too long
    fitness = tempfitness;
    if(counter > 1000){
        if(dfo->getNeighbourTopology() == "RING"){
            dfo->setNeighbourTopology(DFO::RANDOM);
            dfo->setDemocracy(true);
        } else {
            dfo->setNeighbourTopology(DFO::RING);
            dfo->setDemocracy(false);
        }
        weightVsConstRatio *= 0.5;
        weightVsConstRatio = weightVsConstRatio < 0.002 ? 0.002 : weightVsConstRatio;
        counter = 0;
    }
    
    //---
    
    bestPos = dfo->getBestFly()->getPos();
    
    if(reduc) {
        bitset<16> A;//A will hold the binary representation of N with 16 bits precision
        for(int k = 0; k<chunks-1; ++k){
            int N = floor(bestPos[k]+0.5); //input number in base 10
            A=N;
            for (int m = 0; m<dimsPerFeature; ++m){
                if(A[m] >= 0.5) {
                    bestMaxWeight += weights[m+k*dimsPerFeature];
                    for(int j = 0; j<numKnaps; ++j){
                        testCons[j] += constraints[j][m+k*dimsPerFeature];
                    }
                }
            }
            A=0;
        }
        // last chunk ---
        int N = floor(bestPos[chunks-1]+0.5); //input number in base 10
        A=N;
        for (int m = 0; m<lastChunkDim; ++m){
            if(A[m] >= 0.5) {
                bestMaxWeight += weights[m+(chunks-1)*dimsPerFeature];
                for(int j = 0; j<numKnaps; ++j){
                    testCons[j] += constraints[j][m+(chunks-1)*dimsPerFeature];
                }
            }
        }
        A=0;
        // ----
    } else {
        for(int m = 0; m<bestPos.size(); ++m){
            bestPos[m] = floor(bestPos[m] + 0.5);
            if(bestPos[m] >= 0.5){
                bestMaxWeight += weights[m];
                for(int j = 0; j<numKnaps; ++j){
                    testCons[j] += constraints[j][m];
                }
            }
        }
    }
}


// Function for reporting data every N number of cycles or at the end
void Dfo_knap::report(int& i, vector<double>& bestPos, int& bestMaxWeight, vector<int> testCons){
    cout << "\n";
    cout << probID << ", ";

    std::cout << "cycle: " << i <<  "\n";
    std::cout << "algo: " << (dfo->getDemocracy() ? "Best Neighbour" : "Swarm's Best") <<  ", ";
    std::cout << "greed/safety ratio: " << weightVsConstRatio << "\n";
    std::cout << "pop. size: " << dfo->getPopSize() << ", ";
    std::cout << "nghbr topol. used: " << dfo->getNeighbourTopology() << ", ";
    std::cout << "dist thresh: " << dfo->getDt() << "(" <<dfo->getDtRandMode() << ")\n";
    std::cout << "num. neighb. assessed: " << dfo->getNumNeighbours() * 2 << "\n";
    std::cout << "fitness: "<< fitness <<  ", ";
    std::cout << "best fly index: " << dfo->getBestIndex() <<  ", ";
    
    bestPos = dfo->getBestFly()->getPos();
    
    bestMaxWeight = 0;
    
    if(reduc) {
        std::cout << "best fly location: " ;
        bitset<16> A;//A will hold the binary representation of N with 16 bits precision
        for(int k = 0; k<chunks-1; ++k){
            int N = floor(bestPos[k]+0.5); //input number in base 10
            A=N;
            for (int m = 0; m<dimsPerFeature; ++m){
                std::cout << A[m] << "";
                if(A[m] >= 0.5) {
                    bestMaxWeight += weights[m+k*dimsPerFeature];
                    for(int j = 0; j<numKnaps; ++j){
                        testCons[j] += constraints[j][m+k*dimsPerFeature];
                    }
                }
            }
            A=0;
            cout << "(" << dfo->getBestFly()->getPos(k) << ") "; //cout << "| ";
        }
        // last chunk ---
        int N = floor(bestPos[chunks-1]+0.5); //input number in base 10
        A=N;
        for (int m = 0; m<lastChunkDim; ++m){
            std::cout << A[m] << "";
            if(A[m] >= 0.5) {
                bestMaxWeight += weights[m+(chunks-1)*dimsPerFeature];
                for(int j = 0; j<numKnaps; ++j){
                    testCons[j] += constraints[j][m+(chunks-1)*dimsPerFeature];
                }
            }
        }
        A=0;
        cout << "(" << dfo->getBestFly()->getPos((chunks-1)) << ") "; //cout << "| ";
        // ----
        
        std::cout <<  "\n";
    } else {
        for(int m = 0; m<bestPos.size(); ++m){
            bestPos[m] = floor(bestPos[m] + 0.5);
            if(bestPos[m] >= 0.5){
                bestMaxWeight += weights[m];
                for(int j = 0; j<numKnaps; ++j){
                    testCons[j] += constraints[j][m];
                }
            }
        }
        std::cout << "best fly location: " << vect_to_string(bestPos) <<  "\n";
    }
    std::cout << "best fly's suggested fill-ups:"<<  "\n";
    for(int i = 0; i<numKnaps; ++i){
        std::cout << "knap " << i+1 << ": " << testCons[i] << " ";
    }
    std::cout <<  "\n";
    std::cout << "best weight obtained : "<< bestMaxWeight <<  "\n";
    std::cout << "best weight target : "<< optimalWight <<  "\n";
}

