//
//  DFO.hpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#ifndef DFO_hpp
#define DFO_hpp

#include <stdio.h>
#include "Utilis.hpp"

using namespace std;

class DFO {

public:
    // default constructor
    DFO();
    // overloaded constructor where a function is passed in as an argument
    DFO(std::function<double(std::vector<double>)> fitnessFunc);

    // default destructor
    ~DFO();
    
    // wrapper for the DFO algorithm components
    Utilis* pUtilis;
    
    // generate DFO swarm (cycle 0 of the algorithm)
    void const generateSwarm();
    
    // DFO implementation part: evaluate flies, make them interact & update the swarm
    void const updateSwarm();
    
    // ----- singleton needed stuff ---- This class can be implemented only ONCE
    
    // Dont forget to declare these two. C++ 03 way of making sure they
    // are unacceptable otherwise you may accidentally get copies of
    // your singleton appearing.
    
    DFO(DFO const&) = delete;
    void operator=(DFO const&) = delete;
    
    static DFO& getInstance()
    {
        static DFO instance; // Guaranteed to be destroyed.
        // Instantiated on first use.
        return instance;
    }
    // Note: In C++ 11 we can use the better ways of deleting the methods
};

#endif /* DFO_hpp */
