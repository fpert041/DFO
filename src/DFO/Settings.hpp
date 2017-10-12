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
#include <array>
#include <string>

class Fly; // forward declare the existance of a class of type Fly

struct Settings {
    
public:
    
    // dim: the dimensions of the problem
    static const int dim = 10;
    
    // popSize: the size of the population of 'flys'
    static const int popSize = 20;
    
    // disturbance threshold
    static constexpr double dt = 0.001;
    
    // an array of 'empty' fly-objects: it will hold our swarm
    static std::array<Fly, popSize> swarm;
    
    //--------------------------------------------------------
    
    // Variables to hold globally the dimension of the search space of the problem
    static int searchSpaceWidth, searchSpaceHeight;
    
    // Constant to set the maximum number of Fly Evaluations allowed to the program
    static const int FE_allowed = 300000;
    
    // This variable stores the index of the best Fly (whose position is the fittest to solve the problem)
    static int bestIndex;
    
    static const int evalCount = 0;
    
    static const int scaleF = 5;
    
    // Two variables to store globally the indeces of the left and right neighbour of a Fly currencly being checked
    static int leftNeighbour, rightNeighbour;
    
    static std::string evaluationFunctionName;
};


#endif /* Settings_hpp */
