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

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>
#include <bitset>
#include <math.h>
#include <functional>

enum DimensionalReduc { REDUCED, EXTENDED };

class Dfo_knap {
    // variable that will hold the DFO algorithm components
    unique_ptr<DFO> dfo = unique_ptr<DFO>(new DFO());
    
    vector<int> knap_capacity;
    int numKnaps;
    vector<int> weights;
    vector<vector<int>> constraints;
    //std::vector<int> solution {1,1,1,1,0,1,0,0,0,0};
    
    int numObjects;
    int maxWeight;
    vector<int> maxConsts;
    bool reduc = false;

public:
    
    //Dfo_knap();
    Dfo_knap(vector<int>maxCap, std::vector<int> w, vector<vector<int>> c);
    
    void setup(int popSize = 50, DimensionalReduc r = EXTENDED);
    void changeCyclesNum(int newNum);
    void run();
};

#endif /* main_h */

