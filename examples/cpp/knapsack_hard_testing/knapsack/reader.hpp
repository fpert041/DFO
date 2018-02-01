//
//  reader.hpp
//  knapsack
//
//  Created by Francesco Perticarari on 29/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#ifndef reader_hpp
#define reader_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "problem.hpp"

using namespace std;

class Reader {
public:
    Reader(string problemTextPath);
    ~Reader();
    
    vector<Problem*> problems;
    
};

#endif /* reader_hpp */
