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
    
    int knap_capacity = 165;
    std::vector<int> weights {23,31,29,44,53,38,63,85,89,82};
    std::vector<int> profits {92,57,49,68,60,43,67,84,87,72};
    //std::vector<int> solution {1,1,1,1,0,1,0,0,0,0};
    
    int numObjects;
    bool reduc = false;

public:
    
    Dfo_knap();
    Dfo_knap(int maxCap, std::vector<int> w, std::vector<int> p);
    
    void setup(int popSize = 50, DimensionalReduc r = EXTENDED);
    void run();
};

#endif /* main_h */

