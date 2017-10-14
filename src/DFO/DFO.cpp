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

DFO::DFO(){
    pUtilis = new Utilis();
}

DFO::DFO(std::function<double(std::vector<double>)> fitnessFunc){
    pUtilis = new Utilis(fitnessFunc);
}

// ******** DFO destructor *********** //

DFO::~DFO(){
    delete(pUtilis);
    pUtilis = nullptr;
}

//--------------------------------------------------------------------------------
/*********************************************************************************
 *
 * Generate DFO swarm (cycle 0 of the algorithm)
 * - Call this method when you want to start the algorithm and setup the swarm -
 *
 *********************************************************************************/

void const DFO::generateSwarm(){
    // generate swarm
    for (int i = 0; i < GlobalParam::popSize; i++){
        GlobalParam::swarm[i].reset(new Fly(vector<double>(pUtilis->genRandPos())));
        
        pUtilis->findBestFly();
    }
}

//--------------------------------------------------------------------------------
/*********************************************************************************
 *
 * DFO equation implementation: evaluate flies, make them interact & update the swarm
 * - Call this method when you want to run a cycle of the algorithm -
 *
 *********************************************************************************/

void const DFO::updateSwarm(){
    
    if (GlobalParam::evalCount > GlobalParam::FE_allowed)
        return -1;
    
    // ========= EVALUATION Phase =========
    for (int i = 0; i < GlobalParam::popSize; i++)
    {
        // evaluate the fitness of each Fly in the swarm, then leave a record of the fitness value into each fly
        GlobalParam::swarm[i]->setFitness(pUtilis->evaluate(GlobalParam::swarm[i]->getPos()));
    }
    
    // now that each fly knows its fitness, we can check and record which one is the best
    pUtilis->findBestFly();
    
    // ========= INTERACTION Phase =========
    for (int i = 0; i < GlobalParam::popSize; i++) {
        // Elitist approach:
        // ignore the fly with the best index (we keep it as it is)
        if (i == GlobalParam::bestIndex)
            continue;
        
        //// Use the below method if you want to find the closest neighbour in the search space
        // utils.findClosestNeighbours(i);
        
        //// Use the below method if you want to find the closest neighbour in the search space
        pUtilis->getRandF_or_RingT_Neighbours(i, Utilis::RING);
        
        // cout << to_string(GlobalParam::rightNeighbour) + " :: " + to_string(i) + " :: " + to_string(GlobalParam::rightNeighbour) << endl;
        
        // NEIGHBOURS
        double leftP, rightP;
        if (true) {
            leftP = GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
            
            rightP = GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
            
        } else { // THIS VERSION is suitable for gradual and non-steep hills : try it by turning 'true' into 'false'
            double leftDist =  GlobalParam::swarm[i]->getDistance(GlobalParam::leftNeighbour);
            double rightDist = GlobalParam::swarm[i]->getDistance(GlobalParam::rightNeighbour);
            
            leftP = leftDist * GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
            rightP = rightDist * GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
        }
        
        int chosen;
        if (leftP < rightP)
            chosen = GlobalParam::leftNeighbour;
        else
            chosen = GlobalParam::rightNeighbour;
        
        int dCounter = 0;
        // ================== Apply the update equation ========================
        // =====================================================================
        
        vector<double> temp(GlobalParam::dim);
        for (int d = 0; d < GlobalParam::dim; d++) {
            temp[d] = GlobalParam::swarm[chosen]->getPos(d) +
            pUtilis->random(1) * (GlobalParam::swarm[GlobalParam::bestIndex]->getPos(d) - GlobalParam::swarm[i]->getPos(d));// FINAL
            
            // disturbance mechanism
            if(true){
                if (pUtilis->random(1) < GlobalParam::dt)
                {
                    if (true)
                        temp[d] = pUtilis->random(-GlobalParam::searchSpaceWidth, GlobalParam::searchSpaceWidth);
                    else
                        temp[d] = pUtilis->genGaussian(-GlobalParam::searchSpaceWidth/2.0, GlobalParam::searchSpaceWidth/2.0); // alternative stochastic method // turn If statements into FALSE if you want to check it out
                    
                    dCounter++;
                }
            }
            
            //cout << "Disturbances in Fly  #" + to_sring(i) + ": \t" + to_sring(dCounter) << endl;
            GlobalParam::swarm[i]->setPos(temp);
        }
        // ==== // end of interaction phase // ==== //
    }
}
