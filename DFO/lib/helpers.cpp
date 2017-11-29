//
//  helpers.cpp
//  knapsack
//
//  Created by Francesco Perticarari on 29/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include "../include/helpers.hpp"

/* Some helper functions that can come handy when working with DFO and swarm intelligence */

std::string dfoHelpers::vect_to_string(std::vector<double> vec) {
    std::ostringstream oss;
    
    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
                  std::ostream_iterator<float>(oss, ","));
        
        // Now add the last element with no delimiter
        oss << vec.back();
    }
    
    return oss.str();
}

std::string dfoHelpers::vect_to_string(std::vector<int> vec) {
    std::ostringstream oss;
    
    if (!vec.empty())
    {
        // Convert all but the last element to avoid a trailing ","
        std::copy(vec.begin(), vec.end()-1,
                  std::ostream_iterator<int>(oss, ","));
        
        // Now add the last element with no delimiter
        oss << vec.back();
    }
    
    return oss.str();
}

int dfoHelpers::sumVector(std::vector<int> v){
    int max = 0;
    for (int i = 0; i<v.size(); ++i){
        max += v[i];
    }
    return max;
}

double dfoHelpers::sumVector(std::vector<double> v){
    double max = 0;
    for (int i = 0; i<v.size(); ++i){
        max += v[i];
    }
    return max;
}
