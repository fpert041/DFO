//
//  dfo_game.cpp
//  dfo_cards_cpp
//
//  Created by Francesco Perticarari on 21/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//


#include "dfo_game.h"

double print_num()
{
    return 0.0;
}


void Dfo_game::setup() {
    
    // set a fitness function that would work for this problem:
    // we need to check whether a card is in group 0 or 1,
    // then we compute and return out a measure of the "error" that we get for each solution
    dfo->setFitnessFunc(
                                [this](std::vector<double> p) {
                                    int sumGroup0 = 0;
                                    int prodGroup1 = 1;
                                    
                                    double fitness = 0;
                                    
                                    for(int i = 0; i<p.size(); ++i) {
                                        if(p[i] < 0.5) {
                                            sumGroup0 += i+1;
                                        } else {
                                            prodGroup1 *= i+1;
                                        }
                                    }
                                    
                                    int errG0 = abs(sumGroup0 - 36)*10;
                                    int errG1 = abs(prodGroup1 - 360);
                                    
                                    fitness = errG1 + errG0;
                                    
                                    return fitness;
                                    
                                }
    );
    
    // set up a populatin size of 80
    dfo->setPopSize(80);
    
    // set up a dimensionality of 10
    dfo->setDim(10);
    
    // set the range of all the dimensions of the search space
    dfo->setSearchSpaceWidth(1);
    
    // set neighbour-best algorithm rather swarm-best version (which would be prone to fall into local minima)
    dfo->setDemocracy(true);

    
    //---------------------------
    
    // generate the swarm so that it starts off only on the positive hyperoctant of our search space
    /* Note --  In geometry, an orthant or hyperoctant is the analogue in n-dimensional Euclidean space of a quadrant in the plane or an octant in three dimensions.
     */
    dfo->generateSwarmPositiveAxis();
    

}

void Dfo_game::run() {

    // run the algorithm 50 times
    for (int i = 0; i<50; ++i){
        dfo->updateSwarm();
        float fitness = dfo->swarm[dfo->getBestIndex()]->getFitness();
        std::cout << "cycle: " << i+1 << std::endl;
        std::cout << "best fly index: " << dfo->getBestIndex() << std::endl;
        std::cout << "best fly location: " << dfo->getBestFly()->toString() << std::endl;
        std::cout << "fitness: "<< fitness << std::endl;
        if (fitness == 0) {
            std::cout << "iterations needed: "<< i << std::endl;
            std::cout << "---" << std::endl;
            break;
        }
        std::cout << "---" << std::endl;
    }
}
