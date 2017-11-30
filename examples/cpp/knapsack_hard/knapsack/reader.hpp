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

using namespace std;

class Reader {
public:
    Reader();
    
    vector<int*> nKnaps;
    vector<int*> nObjects;
    
    vector<double*> weights;
    vector<double*> capabs;
    vector<double*> constraints;
    
};

#endif /* reader_hpp */
