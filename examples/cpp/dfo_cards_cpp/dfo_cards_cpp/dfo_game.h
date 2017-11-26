//
//  main.h
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#ifndef main_h
#define main_h

#include "DFO.hpp"
#include <iostream>

class Dfo_game {
    // variable that will hold the DFO algorithm components
    unique_ptr<DFO> dfo = unique_ptr<DFO>(new DFO());

public:
    
    void setup();
    void run();
};

#endif /* main_h */
