//
//  Settings.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 10/10/2017.
//

#include "Settings.hpp"


class Settings {
    
public:
    
    // dim: the dimensions of the problem
    static const int dim = 10;
    
    // popSize: the size of the population of 'flys'
    static const int popSize = 20;
    
    // disturbance threshold
    static constexpr double dt = 0.001;
    
    static const Fly fly[popSize];
};

