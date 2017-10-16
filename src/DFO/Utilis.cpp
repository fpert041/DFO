//
//  Utilis.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 11/10/2017.
//

#include "Utilis.hpp"
#include <memory>

//------------------------------------------------------------------------------------
// PUBLIC METHODS
//------------------------------------------------------------------------------------

/* Constructor */

Utilis::Utilis(){
    
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(0, 1); // Each call to dis(gen) generates a new random double
    ran = dis(gen);
    
    dimensions = GlobalParam::dim; // get the dimensions of the current problem from "GlobalParam"
    em = SPHERE; // defaults the evaluation method to SPHERE
    ntt = RING; // defaults the way neighbours are linked with to RING TOPOLOGY
}

Utilis::Utilis(std::function<double(std::vector<double>)> fitness_func){
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(1, 2); // Each call to dis(gen) generates a new random double
    ran = dis(gen);
    
    dimensions = GlobalParam::dim; // get the dimensions of the current problem from "GlobalParam"
    em = CUSTOM; // defaults the evaluation method to CUSTOM
    eval_custom_fitness_func.operator=(fitness_func); // store provided fitness funciton into a variable
    ntt = RING; // defaults the way neighbours are linked with to RING TOPOLOGY
}

//------------------------------------------------------------------------------------

/* Evaluate fly with position vector 'flyPos' using the DEFAULT fitness function (as indicated by the value of the 'em' varable (enum: EvaluationMethod) */

double Utilis::evaluate(vector<double> flyPos){
    switch (em) {
        case CUSTOM:
            GlobalParam::evaluationFunctionName = "Custom Fitness Function";
            return eval_custom_fitness_func(flyPos);
            break;
            
        case SPHERE:
            return std::abs( eval_sphere(flyPos) );
            break;
            
        default:
            return std::abs( eval_sphere(flyPos) );
            break;
    }
}

// Overridden method: Evaluate the fitness of a certain Fly using the PROVIDED fitness function

double Utilis::evaluate(vector<double> flyPos, EvaluationMethod fit_func_id){
    EvaluationMethod oldEm = em;
    em = fit_func_id;
    evaluate(flyPos);
    em = oldEm;
}

//------------------------------------------------------------------------------------

/* Change the offest value by a limited random factor */

void Utilis::shakeOffset() {
    offset += dis(gen)*20. - 10;
}

//------------------------------------------------------------------------------------

/* find the closest 2 neighbours in the swarm for the fly at location 'flyIndex' within the swarm */

void findClosestNeighbours(int flyIndex) {
    double minDistL = 10E15;
    for (int i = 0; i < GlobalParam::popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = GlobalParam::swarm[flyIndex]->getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            GlobalParam::leftNeighbour = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < GlobalParam::popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == GlobalParam::leftNeighbour)
            continue;
        
        double d = GlobalParam::swarm[flyIndex]->getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            GlobalParam::rightNeighbour = i;
        }
    }

}

// overloaded function that stores neighbours' information into each fly

void findClosestNeighbours(int flyIndex, Fly& flyRef) {
    double minDistL = 10E15;
    for (int i = 0; i < GlobalParam::popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = GlobalParam::swarm[flyIndex]->getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            GlobalParam::leftNeighbour = i;
            flyRef.pLeftNeighbour = GlobalParam::swarm[flyIndex];
            flyRef.leftNindex = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < GlobalParam::popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == GlobalParam::leftNeighbour)
            continue;
        
        double d = GlobalParam::swarm[flyIndex]->getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            GlobalParam::rightNeighbour = i;
            flyRef.pRightNeighbour = GlobalParam::swarm[flyIndex];
            flyRef.rightNindex = i;
        }
    }
    
}

//------------------------------------------------------------------------------------

/* Set the closest 2 neighbours in the swarm for the fly at location 'curr' using either RING TOPOLOGY or RANDOMNESS */

void Utilis::getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type) {
    
    if (type == RING) // RING
    {
        GlobalParam::leftNeighbour = curr - 1;
        GlobalParam::rightNeighbour = curr + 1;
        
        if (curr == 0)
            GlobalParam::leftNeighbour = GlobalParam::popSize - 1;
        if (curr == GlobalParam::popSize - 1)
            GlobalParam::rightNeighbour = 0;
    }
    else // RANDOM
    {
        GlobalParam::leftNeighbour = int(dis(gen)*GlobalParam::popSize);
        while (GlobalParam::leftNeighbour == curr){
            GlobalParam::leftNeighbour = int(dis(gen)*GlobalParam::popSize);
        }
        
        GlobalParam::rightNeighbour = dis(gen)*GlobalParam::popSize;
        while ((GlobalParam::rightNeighbour == curr) || (GlobalParam::rightNeighbour == GlobalParam::leftNeighbour))
            GlobalParam::rightNeighbour = int(dis(gen)*GlobalParam::popSize);
    }
    
}

// overloaded funtion to assign neighbours either using ring topology or at random which also stores the information locally into each Fly

void Utilis::getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type, Fly& flyref){
    
    if (type == RING) // RING
    {
        GlobalParam::leftNeighbour = curr - 1;
        flyref.leftNindex = curr - 1;
        flyref.pLeftNeighbour = GlobalParam::swarm[GlobalParam::popSize - 1];
        
        GlobalParam::rightNeighbour = curr + 1;
        flyref.rightNindex = curr + 1;
        flyref.pRightNeighbour = GlobalParam::swarm[GlobalParam::popSize + 1];
        
        if (curr == 0){ // deal with low extreme
            GlobalParam::leftNeighbour = GlobalParam::popSize - 1;
            flyref.leftNindex = curr - 1;
            flyref.pLeftNeighbour = GlobalParam::swarm[GlobalParam::popSize - 1];
        }
        
        if (curr == GlobalParam::popSize - 1){ // deal with high extreme
            GlobalParam::rightNeighbour = 0;
            flyref.rightNindex = 0;
            flyref.pRightNeighbour = GlobalParam::swarm[0];
        }
    }
    else // RANDOM
    {
        GlobalParam::leftNeighbour = dis(gen)*GlobalParam::popSize;
        while (GlobalParam::leftNeighbour == curr){
            int r = int(dis(gen)*GlobalParam::popSize);
            GlobalParam::leftNeighbour = r;
            flyref.leftNindex = r;
            flyref.pLeftNeighbour = GlobalParam::swarm[r];
        }
        
        GlobalParam::rightNeighbour = dis(gen)*GlobalParam::popSize;
        while ((GlobalParam::rightNeighbour == curr) || (GlobalParam::rightNeighbour == GlobalParam::leftNeighbour)){
            int r = int(dis(gen)*GlobalParam::popSize);
            GlobalParam::rightNeighbour = r;
            flyref.rightNindex = r;
            flyref.pRightNeighbour = GlobalParam::swarm[r];
        }
    }
    
}

//------------------------------------------------------------------------------------

/* Find the fly whose position is the current best solution to our problem (fittest) */

void Utilis::findBestFly() {
    double min = 10E10;
    
    for (int i = 0; i < GlobalParam::popSize; i++) {
        if (GlobalParam::swarm[i]->getFitness() < min) {
            min = GlobalParam::swarm[i]->getFitness();
            //cout << "fly: " + to_string(i) + " - BestF: " + to_string(min) << endl;
            GlobalParam::bestIndex = i;
        }
    }
}

//------------------------------------------------------------------------------------

/* Print to console summary of the findings of the algorithm */

void Utilis::printSummary() {
    if (GlobalParam::evalCount % 1000 == 0)
        cout << "\nFE: " + to_string(GlobalParam::evalCount / 1000) + " ===> \n\t"
        + to_string(GlobalParam::swarm[GlobalParam::bestIndex]->getFitness()) + "\t" + to_string(GlobalParam::bestIndex) + "\t"
                           + GlobalParam::swarm[GlobalParam::bestIndex]->toString() << endl;
}

//------------------------------------------------------------------------------------

/* Generate and output a random Fly's position vector */

vector<double> Utilis::genRandPos() {
    vector<double> pos = vector<double>(GlobalParam::dim);
    for (int d = 0; d < GlobalParam::dim; d++){
        //double coordinateLimitL = -GlobalParam::searchSpaceWidth / 2; // deletable for more optimisation //<<<
        //double coordinateLimitR = coordinateLimitL + GlobalParam::searchSpaceWidth;
        pos[d] = -GlobalParam::searchSpaceWidth / 2  + 2 * GlobalParam::searchSpaceWidth / 2   * dis(gen);
    //// pos[d] = dis(gen)*GlobalParam::searchSpaceWidth - GlobalParam::searchSpaceWidth/2;
    }
    return pos;
}

// Alternative version of the method above

vector<double> Utilis::genRandPos2() {
    vector<double> pos = vector<double>(GlobalParam::dim);
    for (int d = 0; d < GlobalParam::dim; d++)
        pos[d] = -GlobalParam::searchSpaceWidth + GlobalParam::searchSpaceWidth / 2 * dis(gen);
    //  pos[d] = dis(gen)*GlobalParam::searchSpaceWidth - GlobalParam::searchSpaceWidth/2;
    
    return pos;
}

//------------------------------------------------------------------------------------

/* Output random number (normal distribution) between '1st arg' and '2nd arg' (if no 2nd arg is pecified it'll be between 0 and the arg passed in) */

double Utilis::random(double from, double to){
    double ranN = dis(gen);
    ranN *= abs(to - from);
    ranN += from;
    return ranN;
}

double Utilis::random(double to){ // overloaded method to allow for 'to' only parameter ot be passed in
    return random(0, to);
}

//------------------------------------------------------------------------------------

/* Given the distribution mean value and its standard deviation (variance),
   generate and return a Gaussian Random number */

double Utilis::genGaussian(double bellMean, double bellStdDev) {
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(bellMean, bellStdDev);
    
    return distribution(generator);
}

//------------------------------------------------------------------------------------
// PRIVATE METHODS
//------------------------------------------------------------------------------------

// FITNESS FUNCTION
// The below methods will return a double indicating the level of fitness of a given vector
// Fitness is calcualted as the

double Utilis::eval_sphere(std::vector<double> flyPos){
    double a = 0;
    for (int i = 0; i < dimensions; i++) {
        a += std::pow(flyPos[i] + offset, 2);
    }
    GlobalParam::evaluationFunctionName = "SPHERE";
    return a;
}

