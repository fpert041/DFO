//
//  Utilis.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 11/10/2017.
//

#include "../include/Utilis.hpp"
#include <memory>

//------------------------------------------------------------------------------------
// PUBLIC METHODS
//------------------------------------------------------------------------------------

/* Constructor */

Utilis::Utilis(){
    
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(0., 1.); // Each call to dis(gen) generates a new random double
    ran = dis(gen);
    
    em = SPHERE; // defaults the evaluation method to SPHERE
    ntt = RING; // defaults the way neighbours are linked with to RING TOPOLOGY (ntt = neighbour topology type)
}

Utilis::Utilis(std::function<double(std::vector<double>)> fitness_func){
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(0., 1.); // Each call to dis(gen) generates a new random double
    ran = dis(gen);
    
    em = CUSTOM; // defaults the evaluation method to CUSTOM
    eval_custom_fitness_func.operator=(fitness_func); // store provided fitness funciton into a variable
    ntt = RING; // defaults the way neighbours are linked with to RING TOPOLOGY
}

//------------------------------------------------------------------------------------

void Utilis::setFitnessFunc(std::function<double(std::vector<double>)> fitness_func){
    eval_custom_fitness_func.operator=(fitness_func); // store provided fitness funciton into a variable
    em = CUSTOM; // defaults the evaluation method to CUSTOM
}

void Utilis::resetFitnessFunc(){
    em = SPHERE; // store provided fitness funciton into a variable
}

void Utilis::setNeighbourTopology(NeighbouringTopologyType nt){
    ntt = nt; // set the neighbouring topology
}

//------------------------------------------------------------------------------------

/* Evaluate fly with position vector 'flyPos' using the DEFAULT fitness function (as indicated by the value of the 'em' varable (enum: EvaluationMethod) */

double Utilis::evaluate(vector<double> flyPos){
    switch (em) {
        case CUSTOM:
            evaluationFunctionName = "Custom Fitness Function";
            return (eval_custom_fitness_func(flyPos));
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
    double e = evaluate(flyPos);
    em = oldEm;
    return(e);
}

//------------------------------------------------------------------------------------

/* Change the offest value by a limited random factor */

void Utilis::shakeOffset() {
    offset += dis(gen)*20. - 10;
}

//------------------------------------------------------------------------------------

/* find the closest 2 neighbours in the swarm for the fly at location 'flyIndex' within the swarm */

void Utilis::findClosestNeighbours(int flyIndex) {
    double minDistL = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = swarm[flyIndex]->getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            leftNeighbour = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == leftNeighbour)
            continue;
        
        double d = swarm[flyIndex]->getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            rightNeighbour = i;
        }
    }

}

// overloaded function that stores neighbours' information into each fly

void Utilis::findClosestNeighbours(int flyIndex, Fly& flyRef) {
    double minDistL = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = swarm[flyIndex]->getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            leftNeighbour = i;
            flyRef.pLeftNeighbour = swarm[flyIndex];
            flyRef.leftNindex = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == leftNeighbour)
            continue;
        
        double d = swarm[flyIndex]->getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            rightNeighbour = i;
            flyRef.pRightNeighbour = swarm[flyIndex];
            flyRef.rightNindex = i;
        }
    }
    
}

//------------------------------------------------------------------------------------

string Utilis::getNeighbourTopology(){ // get the neighbouring topology
    if(ntt == RING) return "RING";
    else return "RANDOM";
}

//------------------------------------------------------------------------------------

/* Set the closest 2 neighbours in the swarm for the fly at location 'curr' using either RING TOPOLOGY or RANDOMNESS */

void Utilis::getRandF_or_RingT_Neighbours(int curr) {
    if (ntt == RING) // RING
    {
        leftNeighbour = curr - 1;
        rightNeighbour = curr + 1;
        
        if (curr == 0)
        leftNeighbour = popSize - 1;
        if (curr == popSize - 1)
        rightNeighbour = 0;
    }
    else // RANDOM
    {
        leftNeighbour = int(dis(gen)*popSize);
        while (leftNeighbour == curr){
            leftNeighbour = int(dis(gen)*popSize);
        }
        
        rightNeighbour = dis(gen)*popSize;
        while ((rightNeighbour == curr) || (rightNeighbour == leftNeighbour))
        rightNeighbour = int(dis(gen)*popSize);
    }
    
}

// overloaded funtion which also stores the information locally into each Fly


void Utilis::getRandF_or_RingT_Neighbours(int curr, Fly& flyref) {
    if (ntt == RING) // RING
    {
        leftNeighbour = curr - 1;
        flyref.leftNindex = curr - 1;
        flyref.pLeftNeighbour = swarm[popSize - 1];
        
        rightNeighbour = curr + 1;
        flyref.rightNindex = curr + 1;
        flyref.pRightNeighbour = swarm[popSize + 1];
        
        if (curr == 0){ // deal with low extreme
            leftNeighbour = popSize - 1;
            flyref.leftNindex = curr - 1;
            flyref.pLeftNeighbour = swarm[popSize - 1];
        }
        
        if (curr == popSize - 1){ // deal with high extreme
            rightNeighbour = 0;
            flyref.rightNindex = 0;
            flyref.pRightNeighbour = swarm[0];
        }
    }
    else // RANDOM
    {
        leftNeighbour = int(dis(gen)*popSize);
        while (leftNeighbour == curr){
            int r = int(dis(gen)*popSize);
            leftNeighbour = r;
            flyref.leftNindex = r;
            flyref.pLeftNeighbour = swarm[r];
        }
        
        rightNeighbour = dis(gen)*popSize;
        while ((rightNeighbour == curr) || (rightNeighbour == leftNeighbour)){
            int r = int(dis(gen)*popSize);
            rightNeighbour = r;
            flyref.rightNindex = r;
            flyref.pRightNeighbour = swarm[r];
        }
    }
    
}

// overloaded funtion to specify how to assign neighbours either using ring topology

void Utilis::getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type) {
    
    if (type == RING) // RING
    {
        leftNeighbour = curr - 1;
        rightNeighbour = curr + 1;
        
        if (curr == 0)
            leftNeighbour = popSize - 1;
        if (curr == popSize - 1)
            rightNeighbour = 0;
    }
    else // RANDOM
    {
        leftNeighbour = int(dis(gen)*popSize);
        while (leftNeighbour == curr){
            leftNeighbour = int(dis(gen)*popSize);
        }
        
        rightNeighbour = dis(gen)*popSize;
        while ((rightNeighbour == curr) || (rightNeighbour == leftNeighbour))
            rightNeighbour = int(dis(gen)*popSize);
    }
    
}

// overloaded funtion to assign neighbours either using ring topology or at random which also stores the information locally into each Fly

void Utilis::getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type, Fly& flyref){
    
    if (type == RING) // RING
    {
        leftNeighbour = curr - 1;
        flyref.leftNindex = curr - 1;
        flyref.pLeftNeighbour = swarm[popSize - 1];
        
        rightNeighbour = curr + 1;
        flyref.rightNindex = curr + 1;
        flyref.pRightNeighbour = swarm[popSize + 1];
        
        if (curr == 0){ // deal with low extreme
            leftNeighbour = popSize - 1;
            flyref.leftNindex = curr - 1;
            flyref.pLeftNeighbour = swarm[popSize - 1];
        }
        
        if (curr == popSize - 1){ // deal with high extreme
            rightNeighbour = 0;
            flyref.rightNindex = 0;
            flyref.pRightNeighbour = swarm[0];
        }
    }
    else // RANDOM
    {
        leftNeighbour = int(dis(gen)*popSize);
        while (leftNeighbour == curr){
            int r = int(dis(gen)*popSize);
            leftNeighbour = r;
            flyref.leftNindex = r;
            flyref.pLeftNeighbour = swarm[r];
        }
        
        rightNeighbour = dis(gen)*popSize;
        while ((rightNeighbour == curr) || (rightNeighbour == leftNeighbour)){
            int r = int(dis(gen)*popSize);
            rightNeighbour = r;
            flyref.rightNindex = r;
            flyref.pRightNeighbour = swarm[r];
        }
    }
    
}

//------------------------------------------------------------------------------------

/* Find the fly whose position is the current best solution to our problem (fittest) */

void Utilis::findBestFly() {
    double min = 10E10;
    
    for (int i = 0; i < popSize; i++) {
        if (swarm[i]->getFitness() < min) {
            min = swarm[i]->getFitness();
            //cout << "fly: " + to_string(i) + " - BestF: " + to_string(min) << endl;
            bestIndex = i;
        }
    }
}

//------------------------------------------------------------------------------------

/* Print to console summary of the findings of the algorithm */

void Utilis::printSummary() {
    if (evalCount % 1000 == 0)
        cout << "\nFE: " + to_string(evalCount / 1000) + " ===> \n\t"
        + to_string(swarm[bestIndex]->getFitness()) + "\t" + to_string(bestIndex) + "\t"
                           + swarm[bestIndex]->toString() << endl;
}

//------------------------------------------------------------------------------------

// turn a linear dimensional space into a "Torus-like" space, by wrapping dimensions
int Utilis::torus( int n, int inDim )
{
    int threshold = getSearchSpaceWidth(inDim);
    int result = n;
    if ( n >= threshold )
        result = n % threshold;
    else if ( n < 0 )
        result = threshold-n; //?
    
    return result;
}

//------------------------------------------------------------------------------------

/* Generate and output a random Fly's position vector */

vector<double> Utilis::genRandPos() {
    vector<double> pos = vector<double>(dim);
    for (int d = 0; d < dim; d++){
        //double coordinateLimitL = -searchSpaceWidth[d] / 2; // deletable for more optimisation //<<<
        //double coordinateLimitR = coordinateLimitL + searchSpaceWidth[d];
        pos[d] = -searchSpaceWidth[d] / 2.  + 2. * searchSpaceWidth[d] / 2.   * dis(gen);
    //// pos[d] = dis(gen)*searchSpaceWidth[d] - searchSpaceWidth[d]/2;
    }
    return pos;
}

// Alternative version of the method above

vector<double> Utilis::genRandPos2() {
    vector<double> pos = vector<double>(dim);
    for (int d = 0; d < dim; d++)
        pos[d] = -searchSpaceWidth[d] + searchSpaceWidth[d] / 2. * dis(gen);
    //  pos[d] = dis(gen)*searchSpaceWidth[d] - searchSpaceWidth[d]/2;
    
    return pos;
}

// Alternative version of the method above, where the search space is only positive (== to searchSpaceWidth[d])
vector<double> Utilis::genRandPosPositive() {
    vector<double> pos = vector<double>(dim);
    for (int d = 0; d < dim; d++){
        pos[d] = random(searchSpaceWidth[d]);
    }
    return pos;
}


//------------------------------------------------------------------------------------

/* Output random number (normal distribution) between '1st arg' and '2nd arg' (if no 2nd arg is pecified it'll be between 0 and the arg passed in) */

double Utilis::random(double from, double to){
    double ranN = dis(gen);
    ranN *= (to - from);
    ranN += from;
    // cout << ranN << endl;
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
    
    return distribution(gen);
}

//------------------------------------------------------------------------------------

 // set the leader of the swarm externally
void Utilis::setLeader(std::vector<double> newF){
    if(newF.size() == swarm[0]->getPos().size()){
        swarm[0].reset(new Fly(newF, this));
    } else {
        std::cout << "THE SWARM IS NOT COMPATIBLE WITH THE INPUT FLY's POSITION" << std::endl;
    }
}

//------------------------------------------------------------------------------------
// PRIVATE METHODS
//------------------------------------------------------------------------------------

// FITNESS FUNCTION
// The below methods will return a double indicating the level of fitness of a given vector
// Fitness is calcualted as the

double Utilis::eval_sphere(std::vector<double>& flyPos){
    double a = 0;
    for (int i = 0; i < dim; ++i) {
        a += std::pow(flyPos[i] + offset, 2.);
    }
    evaluationFunctionName = "SPHERE";
    return a;
}

