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

class Fly; // forward declare the existance of a class of type Fly

struct GlobalParam {

 
    // dim: the dimensions of the problem
    static int dim;
    // popSize: the size of the population of 'flys'
    static int popSize;
    
    // disturbance threshold
    static double dt;
    
    // an array of 'empty' fly-objects: it will hold our swarm
    static std::vector<std::shared_ptr<Fly>> swarm;
    
    // Constant to set the maximum number of Fly Evaluations allowed to the program
    static int FE_allowed;
    
    // This variable stores the index of the best Fly (whose position is the fittest to solve the problem)
    static int bestIndex;
    
    // Counter for the evaluations carried out in the program
    static int evalCount;
    
    // Two variables to store globally the indeces of the left and right neighbour of a Fly currencly being checked
    static int leftNeighbour, rightNeighbour;
    
    // This varaible stores name of the function used to perform the evaluation of Flies
    static std::string evaluationFunctionName;
    
    // is the problem being visualised across a 2d surface space?
    const static bool mod_2d = true;
    
    //--------------------------------------------------------
    
    // Variables to hold globally the dimension of the search space of the problem
    static int searchSpaceWidth, searchSpaceHeight;
    
public:
    
    // ----- this struct cannot be instantiated: -----
    
    // C++ 03 way of making sure the below constructors
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    GlobalParam() = delete;
    GlobalParam(GlobalParam const&) = delete;
    void operator=(GlobalParam const&) = delete;
    
    // Note: In C++ 11 we can use the better ways of deleting the methods
};


#endif /* Settings_hpp */
