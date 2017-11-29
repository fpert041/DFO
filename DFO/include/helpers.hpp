//
//  helpers.cpp
//  knapsack
//
//  Created by Francesco Perticarari on 29/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#ifndef dfoHelpers_hpp
#define dfoHelpers_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <sstream>

/* Some helper functions that can come handy when working with DFO and swarm intelligence */

namespace dfoHelpers {
    
    std::string vect_to_string(std::vector<double> vec);
    std::string vect_to_string(std::vector<int> vec);
    
    int sumVector(std::vector<int> v);
    double sumVector(std::vector<double> v);

}

#endif
