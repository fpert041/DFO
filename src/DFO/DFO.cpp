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
    
    // Set up global parameters for the problem space -> this works well for visualising the problem
    // But I wonder how it would work on other search-spaces //************INVESTIGATE W/ MOHAMMAD IF POSSIBLE ****//<<<
    
    GlobalParam::searchSpaceWidth = 100; // at present this is the RANGE of the value of each dimension (search space coordinates)
    
    // generate swarm
    int size = GlobalParam::popSize;
    GlobalParam::swarm.clear();
    for (int i = 0; i < size; i++){
        GlobalParam::swarm.push_back(shared_ptr<Fly>(new Fly(pUtilis->genRandPos()) ) );
    }

    pUtilis->findBestFly();

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
    for (int i = 0; i < GlobalParam::popSize; ++i)
    {
        // evaluate the fitness of each Fly in the swarm, then leave a record of the fitness value into each fly
        GlobalParam::swarm[i]->setFitness(
                                              pUtilis->evaluate(GlobalParam::swarm[i]->getPos())
                                          );
    }
    
    // now that each fly knows its fitness, we can check and record which one is the best
    pUtilis->findBestFly();
    // ========= INTERACTION Phase =========
    for (int k = 0; k < GlobalParam::popSize; k++) {
        // Elitist approach:
        // ignore the fly with the best index (we keep it as it is)
        if (k == GlobalParam::bestIndex)
            continue;
        
        //// Use the below method if you want to find the closest neighbour in the search space
        // utils.findClosestNeighbours(i);
        
        //// Use the below method if you want to find the closest neighbour in the search space
        pUtilis->getRandF_or_RingT_Neighbours(k, Utilis::RING);
        
        // cout << to_string(GlobalParam::rightNeighbour) + " :: " + to_string(i) + " :: " + to_string(GlobalParam::rightNeighbour) << endl;
        
        // NEIGHBOURS
        double leftP, rightP;
        if (true) {
            leftP = GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
            
            rightP = GlobalParam::swarm[GlobalParam::rightNeighbour]->getFitness();
            
        } else { // THIS VERSION is suitable for gradual and non-steep hills : try it by turning 'true' into 'false'
            double leftDist =  GlobalParam::swarm[k]->getDistance(GlobalParam::leftNeighbour);
            double rightDist = GlobalParam::swarm[k]->getDistance(GlobalParam::rightNeighbour);
            
            leftP = leftDist * GlobalParam::swarm[GlobalParam::leftNeighbour]->getFitness();
            rightP = rightDist * GlobalParam::swarm[GlobalParam::rightNeighbour]->getFitness();
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
            // debug //
            
           // cout<< "fly n# " + to_string(k) + " / dim: " + to_string(d) << endl;
            //cout << "  val: " + to_string(GlobalParam::swarm[k]->getPos(d))<< endl;
            
                 // it seems like the best neighbour is on the wrong side
                //cout << "fly n# " + to_string(k) + " out of " + to_string(GlobalParam::dim) + " " + to_string(GlobalParam::swarm[GlobalParam::bestIndex]->getPos(d) - GlobalParam::swarm[k]->getPos(d)) << endl;
            // endDebug //
            
            /* ELITIST (easier to find one solution but that's all you get) */
            temp[d] =
                        GlobalParam::swarm[chosen]->getPos(d) +
                        pUtilis->random(1) *
                        (GlobalParam::swarm[GlobalParam::bestIndex]->getPos(d) - GlobalParam::swarm[k]->getPos(d));
                        // FINAL // <<<<<<<< why does it get stack with  random [0,1] and works with random [-1, 1]???
            
            
            /* NON-ELITIST (harder to find a solution but you can find clusterings that indicate more than 1 solution) */
            /*******************************************************************************************************
            temp[d] =
                         GlobalParam::swarm[chosen]->getPos(d) +
                         pUtilis->random(1) *
                         (GlobalParam::swarm[chosen]->getPos(d) - GlobalParam::swarm[k]->getPos(d));
                         // FINAL
             
             *******************************************************************************************************/
            
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
        }
        GlobalParam::swarm[k]->setPos(temp);
        // ==== // end of interaction phase // ==== //
        
    }
    GlobalParam::evalCount ++;
}
