//
//  reader.cpp
//  knapsack
//
//  Created by Francesco Perticarari on 29/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include "reader.hpp"

Reader::Reader(){
    
    // WHEN READING A FILE AT RUNTIME, THE PATH IS FROM THE APP (e.g. in Build/Products/Debug)
    fstream myfileX("../../../data/hard_probs.txt", ios_base::in);
    ifstream myfile("../../../data/hard_probs.txt", ifstream::in);
    
    if(!myfile.is_open())
        printf("could not read file!\n");
    else
        printf("file opened correctly\n");
    
    int val;
    string str;
    while (myfile >> val >> str)
    {
        printf("%i ", val);
        printf("%s ", str.c_str());
    }
    
    //printf("press key to terminate program\n");
    //getchar();
    
}

