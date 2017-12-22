//
//  DFO.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 14/10/2017.
//

#include "../DFO.hpp"

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

// ---- setters and getters -----

// keep fly's coordinates within the given search space width
void const DFO::setConstrainPos(bool status){
    constrainPositions = status;
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
    
    // generate swarm
    int size = popSize;
    swarm.clear();
    for (int i = 0; i < size; i++){
        swarm.push_back(shared_ptr<Fly>(new Fly(genRandPos(), this)));
    }

    findBestFly();

}

void const DFO::generateSwarmPositiveAxis(){
    
    // Set up global parameters for the problem space -> this works well for visualising the problem
    // But I wonder how it would work on other search-spaces //************INVESTIGATE W/ MOHAMMAD IF POSSIBLE ****//<<<
    
    // generate swarm
    int size = popSize;
    swarm.clear();
    for (int i = 0; i < size; i++){
        swarm.push_back(shared_ptr<Fly>(new Fly(genRandPosPositive(), this)));
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
    vector<double> temp(dim);
    
    if (evalCount > FE_allowed)
        return void();
    
    // ========= EVALUATION Phase =========
    for (int i = 0; i < popSize; ++i)
    {
        // evaluate the fitness of each Fly in the swarm, then leave a record of the fitness value into each fly
        swarm[i]->setFitness( evaluate( swarm[i]->getPos() ) );
    }
    
    // now that each fly knows its fitness, we can check and record which one is the best
    findBestFly();
    // ========= INTERACTION Phase =========
    for (int k = 0; k < popSize; ++k) {
        // Elitist approach:
        // ignore the fly with the best index (we keep it as it is)
        if (k == bestIndex)
            continue;
        
        //// Use the below method if you want to find the closest neighbour in the search space
        // utils.findClosestNeighbours(i);
        
        //// Use the below method if you want to find the closest neighbour in the search space
        getRandF_or_RingT_Neighbours(k);
        
        // cout << to_string(rightNeighbour) + " :: " + to_string(i) + " :: " + to_string(rightNeighbour) << endl;
        
        // NEIGHBOURS
        double leftP = 10E15, rightP = 10E15;
        int leftInd = -1, rightInd = -1, chosen = -1;
        
        if (/* DISABLES CODE */ (true)) {
            for(int i = 0; i<numNeighbours; ++i){
                if(swarm[leftNeighbour[i]]->getFitness() < leftP){
                    leftP = swarm[leftNeighbour[i]]->getFitness();
                    leftInd = i;
                }
                if(swarm[rightNeighbour[i]]->getFitness() < rightP){
                    rightP = swarm[rightNeighbour[i]]->getFitness();
                    rightInd = i;
                }
            }
            
        } else { // THIS VERSION is suitable for gradual and non-steep hills : try it by turning 'true' into 'false'
            for(int i = 0; i<numNeighbours; ++i){
                double leftDist =  swarm[k]->getDistance(leftNeighbour[i]);
                double rightDist = swarm[k]->getDistance(rightNeighbour[i]);
                if(swarm[leftNeighbour[i]]->getFitness() < leftP){
                    leftP =  leftDist * swarm[leftNeighbour[i]]->getFitness();
                    leftInd = i;
                }
                if(swarm[rightNeighbour[i]]->getFitness() < rightP){
                    rightP = rightDist * swarm[rightNeighbour[i]]->getFitness();
                    rightInd = i;
                }
            }
        }
        
        if (leftP < rightP)
            chosen = leftNeighbour[leftInd];
        else
            chosen = rightNeighbour[rightInd];
    
        int dCounter = 0;
        
        // ================== Apply the update equation ========================
        // =====================================================================
        
        for (int d = 0; d < dim; ++d) {
            
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
                    if (drm == UNI)
                        temp[d] = random(0., double(searchSpaceWidth[d]));
                    else{
                        //temp[d] = genGaussian(double(searchSpaceWidth[d])/2., double(searchSpaceWidth[d])/2.); // alternative stochastic method // (more likely towards middle of search space range)
                        temp[d] = genGaussian(searchSpaceWidth[d], searchSpaceWidth[d]);// (more towards the upper end of search space range)
                        if(temp[d]>searchSpaceWidth[d])
                            temp[d]-=searchSpaceWidth[d];
                    }
                    
                    dCounter++;
                }
            }
            
            // <<<<<<<<<<<<<<<<<   constrain dimensions to fit the range specified (bouncing off the edges)
            if (constrainPositions) {
                if ( temp[d] > searchSpaceWidth[d] ) temp[d] = searchSpaceWidth[d];//   searchSpaceWidth[d]-fmod(temp[d], searchSpaceWidth[d])*std::min(abs(genGaussian(0, 1)), 1.0);
                if (temp[d] < 0.) temp[d] =  0;//fmod(abs(temp[d]), searchSpaceWidth[d])*std::min(abs(genGaussian(0, 1)), 1.0);
            }
            
            //cout << "Disturbances in Fly  #" + to_sring(i) + ": \t" + to_sring(dCounter) << endl;
        }
        swarm[k]->setPos(temp);
    }
    // ==== // end of interaction phase // ==== //
    evalCount ++;
}
