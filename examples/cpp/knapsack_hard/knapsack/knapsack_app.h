//
//  main.h
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#ifndef main_h
#define main_h

#define E 2.7182818284590452353602874713527

#include "../../../../DFO/DFO.hpp"
#include "problem.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <bitset>
#include <math.h>
#include <functional>
#include <exception>

enum DimensionalReduc { REDUCED, EXTENDED };

class DimensionsPerFeatureError: public exception
{
    virtual const char* what() const throw()
    {
        return "You Must only use 1, 2, 4, 8, or 16";
    }
};

class Dfo_knap {
    // variable that will hold the DFO algorithm components
    unique_ptr<DFO> dfo = unique_ptr<DFO>(new DFO());
    
    vector<int> knap_capacity;
    int numKnaps;
    vector<int> weights;
    vector<vector<int>> constraints;
    int optimalWight;
    
    int numObjects;
    int maxWeight;
    vector<int> maxConsts;
    
    Problem* pProblemData = nullptr;
    
    bool reduc = false;
    int dimsPerFeature = 4; // keep it less than 17 AND a power of 2!
    int lastChunkDim = 0;
    int chunks = 1;
    int newFtSize = 1;

public:
    
    Dfo_knap(); // generate a DFO model to solve example problem instance
    Dfo_knap(Problem& data); // model constructors that take in externally define problems
    Dfo_knap(Problem* data);
    Dfo_knap(vector<int>maxCap, std::vector<int> w, vector<vector<int>> c, int targetOptimum);
    
    void setup(int popSize = 50, DimensionalReduc r = EXTENDED, int ftPerDim = 4);
    void changeCyclesNum(int newNum);
    void run();
    
    DimensionsPerFeatureError myex;
};

#endif /* main_h */

