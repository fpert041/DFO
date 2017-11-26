//
//  DFO.hpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#ifndef DFO_hpp
#define DFO_hpp

#include <stdio.h>
#include "include/Utilis.hpp"

using namespace std;

class DFO : public Utilis {
protected:
    
    bool constrainPositions = false;

public:
    // default constructor
    DFO();
    // overloaded constructor where a function is passed in as an argument
    DFO(std::function<double(std::vector<double>)> fitnessFunc);

    // default destructor
    ~DFO();
    
    // generate DFO swarm (cycle 0 of the algorithm)
    void const generateSwarm();
    
    // generate DFO swarm (cycle 0 of the algorithm) using only the positive axis of each dimensions
    void const generateSwarmPositiveAxis();
    
    // DFO implementation part: evaluate flies, make them interact & update the swarm
    void const updateSwarm();
    
    // keep fly's coordinates within the given search space width
    void const setConstrainPos(bool status);
    
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
