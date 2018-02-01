//
//  problem.cpp
//  knapsack
//
//  Created by Francesco Perticarari on 03/12/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include "problem.hpp"
#include <math.h>
#include <vector>
#include <array>
#include <numeric>

using namespace std;

double mean(vector<double>& v){
    double sum = std::accumulate(std::begin(v), std::end(v), 0.0);
    return sum / v.size();
}

double stDev(vector<double>& v){
    double m = mean(v);
    double accum = 0.0;
    std::for_each (std::begin(v), std::end(v), [&](const double d) {
        accum += (d - m) * (d - m);
    });
    return sqrt(accum / (v.size()-1));
}
