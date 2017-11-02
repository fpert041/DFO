//
//  DFO.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include "DFO.hpp"

//--------------------------------------------------------------------------------
/*********************************************************************************
 *
 *      DFO Constructors:
 *
 * - Call this method when you want to instantiate the algorithm and setup the swarm -
 * -- You have 2 versions. The default one will set up the algorithm to be run  --
 * -- on a test problem space (by default the "benchmark" SHPERE function) --
 * -- The other version allows you to pass in a FITNESS FUNCTION tha will be --
 * -- used to evaluate each Fly: pass in the function that tests your solutions --
 *
 *********************************************************************************/

DFO::DFO(){}

DFO::DFO(std::function<double(std::vector<double>)> fitnessFunc) : Utilis(fitnessFunc){}

// ******** DFO destructor *********** //

DFO::~DFO(){}

//--------------------------------------------------------------------------------
/*********************************************************************************
 *
 * Generate DFO swarm (cycle 0 of the algorithm)
 * - Call this method when you want to start the algorithm and setup the swarm -
 *
 *********************************************************************************/

void const DFO::generateSwarm(){
    
    // Set up global parameters for the problem space -> this works well for visualising the problem
    // But I wonder how it would work on other search-spaces //************INVESTIGATE W/ MOHAMMAD IF POSSIBLE ****//<<<
    
    // generate swarm
    int size = popSize;
    swarm.clear();
    for (int i = 0; i < size; i++){
        swarm.push_back(shared_ptr<Fly>(new Fly(genRandPos(), this)));
    }

    findBestFly();

}

//--------------------------------------------------------------------------------
/*********************************************************************************
 *
 * DFO equation implementation: evaluate flies, make them interact & update the swarm
 * - Call this method when you want to run a cycle of the algorithm -
 *
 *********************************************************************************/

void const DFO::updateSwarm(){
    
    if (evalCount > FE_allowed)
        return -1;
    
    // ========= EVALUATION Phase =========
    for (int i = 0; i < popSize; ++i)
    {
        // evaluate the fitness of each Fly in the swarm, then leave a record of the fitness value into each fly
        swarm[i]->setFitness( evaluate(swarm[i]->getPos()) );
    }
    
    // now that each fly knows its fitness, we can check and record which one is the best
    findBestFly();
    // ========= INTERACTION Phase =========
    for (int k = 0; k < popSize; k++) {
        // Elitist approach:
        // ignore the fly with the best index (we keep it as it is)
        if (k == bestIndex)
            continue;
        
        //// Use the below method if you want to find the closest neighbour in the search space
        // utils.findClosestNeighbours(i);
        
        //// Use the below method if you want to find the closest neighbour in the search space
        getRandF_or_RingT_Neighbours(k, RING);
        
        // cout << to_string(rightNeighbour) + " :: " + to_string(i) + " :: " + to_string(rightNeighbour) << endl;
        
        // NEIGHBOURS
        double leftP, rightP;
        if (true) {
            leftP = swarm[leftNeighbour]->getFitness();
            
            rightP = swarm[rightNeighbour]->getFitness();
            
        } else { // THIS VERSION is suitable for gradual and non-steep hills : try it by turning 'true' into 'false'
            double leftDist =  swarm[k]->getDistance(leftNeighbour);
            double rightDist = swarm[k]->getDistance(rightNeighbour);
            
            leftP = leftDist * swarm[leftNeighbour]->getFitness();
            rightP = rightDist * swarm[rightNeighbour]->getFitness();
        }
        
        int chosen;
        if (leftP < rightP)
            chosen = leftNeighbour;
        else
            chosen = rightNeighbour;
        
        int dCounter = 0;
        
        // ================== Apply the update equation ========================
        // =====================================================================
        
        vector<double> temp(dim);
        for (int d = 0; d < dim; d++) {
            
            if(!democracy){
            /* ELITIST (easier to find one solution but that's all you get) */
            temp[d] =
                        swarm[chosen]->getPos(d) + random(1) *
                        (swarm[bestIndex]->getPos(d) - swarm[k]->getPos(d));
                        // FINAL // <<<<<<<< why does it get stack with  random [0,1] and works with random [-1, 1]???
            
            } else {
            /* NON-ELITIST (harder to find a solution but you can find clusterings that indicate more than 1 solution) */
            temp[d] =
                         swarm[chosen]->getPos(d) + random(1) *
                         (swarm[chosen]->getPos(d) - swarm[k]->getPos(d));
                         // FINAL
            }
            
            // disturbance mechanism
            if(true){
                if (random(1) < dt)
                {
                    if (true)
                        temp[d] = random(-searchSpaceWidth[d], searchSpaceWidth[d]);
                    else
                        temp[d] = genGaussian(-searchSpaceWidth[d]/2.0, searchSpaceWidth[d]/2.0); // alternative stochastic method // turn If statements into FALSE if you want to check it out
                    
                    dCounter++;
                }
            }
            
            //cout << "Disturbances in Fly  #" + to_sring(i) + ": \t" + to_sring(dCounter) << endl;
        }
        swarm[k]->setPos(temp);
    }
    // ==== // end of interaction phase // ==== //
    evalCount ++;
}
