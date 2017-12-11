//
//  Settings.hpp
//
//  Created by Francesco Perticarari on 10/10/2017.
//
//  THIS STRUCTURE PROVIDES A CONTAINER OF STATIC DATA ELEMENTS AND PARAMETER
//  These constants and variables set up the context where the DFO swarm will operate
//  They also specify the size of the agents' swarm and provide memeory holders for the elements algorithm
//

#ifndef Settings_hpp
#define Settings_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <memory>
#include <iostream>

class Fly; // forward declare the existance of a class of type Fly

class GlobalParam {
    
public:
    enum DtRanMode { UNI, GAUSS};
    
protected:
    
    // keep leader in the equation or not
    bool democracy;
    
    // dim: the dimensions of the problem
    int dim;
    // popSize: the size of the population of 'flys'
    int popSize;
    
    // disturbance threshold
    double dt;
    
    // Constant to set the maximum number of Fly Evaluations allowed to the program
    int FE_allowed;
    
    // This variable stores the index of the best Fly (whose position is the fittest to solve the problem)
    int bestIndex;
    
    // Counter for the evaluations carried out in the program
    int evalCount;
    
    // Two variables to store globally the indeces of the left and right neighbour of a Fly currencly being checked
    int leftNeighbour, rightNeighbour;
    
    // This varaible stores name of the function used to perform the evaluation of Flies
    std::string evaluationFunctionName;
    
    // Variables to hold globally the dimension of the search space of the problem
    std::vector<int> searchSpaceWidth;
    
    // Parameter for the type of randomness governing the disturbance
    DtRanMode drm;
    
public:
    
    // an array of 'empty' fly-objects: it will hold our swarm
    std::vector<std::shared_ptr<Fly>> swarm;
    
    // ---------- Interface ----------
    
    GlobalParam();
    
    // -- setters --
    void setFEAllowed(double num);
        // Constant to set the maximum number of Fly Evaluations allowed to the program
    
    void setDt(double inDt);
        // disturbance threshold
    
    void setDim(int dims);
        // dim: the dimensions of the problem
    
    void setPopSize(int inPopSize);
        // popSize: the size of the population of 'flys'
    
    void setDemocracy(bool dem);
        // keep leader (best fly) in the equation or not
    
    void setSearchSpaceWidth(int width);
        // the size (range) of each dimension (can have a range of +/-)

    void setSearchSpaceWidth(int dim, int width);
        // set the size (range) of a specific dimension (can have a range of +/-)
    
    void setDtRandMode(DtRanMode mode);
        // set the type of randomness governing the disturbance
    
    void setSwarm(std::vector<std::shared_ptr<Fly>> newS);
        // set the swarm
    
    // -- getters --
    
    std::vector<std::shared_ptr<Fly>> getSwarm();
    
    std::shared_ptr<Fly> getBestFly();
    
    bool getDemocracy();
    
    std::vector<int> getSearchSpaceWidth();
    
    int getSearchSpaceWidth(int dim);
    
    int getBestIndex();
    
    std::string getEvalFuncName();
    
    int getEvalCount();
    
    int getPopSize();
    
    int getDim();
    
    int getFEAllowed();
    
    float getDt();
    
    std::string getDtRandMode();
    
};


#endif /* Settings_hpp */
