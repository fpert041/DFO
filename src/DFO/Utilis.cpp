//
//  Utilis.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 11/10/2017.
//

#include "Utilis.hpp"

//------------------------------------------------------------------------------------
// PUBLIC METHODS
//------------------------------------------------------------------------------------

/* Constructor */

Utilis::Utilis(){
    
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(1, 2); // Each call to dis(gen) generates a new random double
    ran = dis(gen);
    
    dimensions = Settings::dim; // get the dimensions of the current problem from "Settings"
    em = SPHERE; // defaults the evaluation method to SPHERE
    ntt = RING; // defaults the way neighbours are linked with to RING TOPOLOGY
}

//------------------------------------------------------------------------------------

/* Evaluare fly with position vector 'flyPos' */

double Utilis::evaluate(vector<double> flyPos){
    switch (em) {
        case SPHERE:
            return std::abs( eval_sphere(flyPos) );
            break;
            
        default:
            return std::abs( eval_sphere(flyPos) );
            break;
    }
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
    for (int i = 0; i < Settings::popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = Settings::swarm[flyIndex].getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            Settings::leftNeighbour = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < Settings::popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == Settings::leftNeighbour)
            continue;
        
        double d = Settings::swarm[flyIndex].getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            Settings::rightNeighbour = i;
        }
    }

}

// overloaded function that stores neighbours' information into each fly

void findClosestNeighbours(int flyIndex, Fly& flyRef) {
    double minDistL = 10E15;
    for (int i = 0; i < Settings::popSize; i++) {
        if (i == flyIndex)
            continue;
        
        double d = Settings::swarm[flyIndex].getDistance(i);
        if (d < minDistL) {
            minDistL = d;
            Settings::leftNeighbour = i;
            flyRef.pLeftNeighbour = &Settings::swarm[flyIndex];
            flyRef.leftNindex = i;
        }
    }
    
    double minDistR = 10E15;
    for (int i = 0; i < Settings::popSize; i++) {
        if (i == flyIndex)
            continue;
        if (i == Settings::leftNeighbour)
            continue;
        
        double d = Settings::swarm[flyIndex].getDistance(i);
        if (d < minDistR) {
            minDistR = d;
            Settings::rightNeighbour = i;
            flyRef.pRightNeighbour = &Settings::swarm[flyIndex];
            flyRef.rightNindex = i;
        }
    }
    
}

//------------------------------------------------------------------------------------

/* Set the closest 2 neighbours in the swarm for the fly at location 'curr' using either RING TOPOLOGY or RANDOMNESS */

void Utilis::getRandF_or_RingT_Neighbours(int curr, bool topology) {
    
    if (topology) // RING
    {
        Settings::leftNeighbour = curr - 1;
        Settings::rightNeighbour = curr + 1;
        
        if (curr == 0)
            Settings::leftNeighbour = Settings::popSize - 1;
        if (curr == Settings::popSize - 1)
            Settings::rightNeighbour = 0;
    }
    else // RANDOM
    {
        Settings::leftNeighbour = int(dis(gen)*Settings::popSize);
        while (Settings::leftNeighbour == curr){
            Settings::leftNeighbour = int(dis(gen)*Settings::popSize);
        }
        
        Settings::rightNeighbour = dis(gen)*Settings::popSize;
        while ((Settings::rightNeighbour == curr) || (Settings::rightNeighbour == Settings::leftNeighbour))
            Settings::rightNeighbour = int(dis(gen)*Settings::popSize);
    }
    
}

// overloaded funtion to assign neighbours either using ring topology or at random which also stores the information locally into each Fly

void Utilis::getRandF_or_RingT_Neighbours(int curr, bool topology, Fly& flyref){
    
    if (topology) // RING
    {
        Settings::leftNeighbour = curr - 1;
        flyref.leftNindex = curr - 1;
        flyref.pLeftNeighbour = &Settings::swarm[Settings::popSize - 1];
        
        Settings::rightNeighbour = curr + 1;
        flyref.rightNindex = curr + 1;
        flyref.pRightNeighbour = &Settings::swarm[Settings::popSize + 1];
        
        if (curr == 0){ // deal with low extreme
            Settings::leftNeighbour = Settings::popSize - 1;
            flyref.leftNindex = curr - 1;
            flyref.pLeftNeighbour = &Settings::swarm[Settings::popSize - 1];
        }
        
        if (curr == Settings::popSize - 1){ // deal with high extreme
            Settings::rightNeighbour = 0;
            flyref.rightNindex = 0;
            flyref.pRightNeighbour = &Settings::swarm[0];
        }
    }
    else // RANDOM
    {
        Settings::leftNeighbour = dis(gen)*Settings::popSize;
        while (Settings::leftNeighbour == curr){
            int r = int(dis(gen)*Settings::popSize);
            Settings::leftNeighbour = r;
            flyref.leftNindex = r;
            flyref.pLeftNeighbour = &Settings::swarm[r];
        }
        
        Settings::rightNeighbour = dis(gen)*Settings::popSize;
        while ((Settings::rightNeighbour == curr) || (Settings::rightNeighbour == Settings::leftNeighbour)){
            int r = int(dis(gen)*Settings::popSize);
            Settings::rightNeighbour = r;
            flyref.rightNindex = r;
            flyref.pRightNeighbour = &Settings::swarm[r];
        }
    }
    
}

//------------------------------------------------------------------------------------

/* Find the fly whose position is the current best solution to our problem (fittest) */

void Utilis::findBestFly() {
    double min = 10E10;
    
    for (int i = 0; i < Settings::popSize; i++) {
        if (Settings::swarm[i].getFitness() < min) {
            min = Settings::swarm[i].getFitness();
            Settings::bestIndex = i;
        }
    }
}

//------------------------------------------------------------------------------------

/* Print to console summary of the findings of the algorithm */

void Utilis::printSummary() {
    if (Settings::evalCount % 1000 == 0)
        cout << "\nFE: " + to_string(Settings::evalCount / 1000) + " ===> \n\t"
        + to_string(Settings::swarm[Settings::bestIndex].getFitness()) + "\t" + to_string(Settings::bestIndex) + "\t"
                           + Settings::swarm[Settings::bestIndex].toString() << endl;
}

//------------------------------------------------------------------------------------

/* Generate and output a random Fly's position vector */

vector<double> Utilis::genRandPos() {
    vector<double> pos = vector<double>(Settings::dim);
    for (int d = 0; d < Settings::dim; d++)
        pos[d] = -Settings::searchSpaceWidth / 2 + 2 * Settings::searchSpaceWidth / 2 * dis(gen);
    //// pos[d] = dis(gen)*Settings::searchSpaceWidth - Settings::searchSpaceWidth/2;
    
    return pos;
}

// Alternative version of the method above

vector<double> Utilis::genRandPos2() {
    vector<double> pos = vector<double>(Settings::dim);
    for (int d = 0; d < Settings::dim; d++)
        pos[d] = -Settings::searchSpaceWidth + Settings::searchSpaceWidth / 2 * dis(gen);
    //  pos[d] = dis(gen)*Settings::searchSpaceWidth - Settings::searchSpaceWidth/2;
    
    return pos;
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

double Utilis::eval_sphere(std::vector<double> flyPos){
    double a = 0;
    for (int i = 0; i < dimensions; i++) {
        a = a + std::pow(flyPos[i] + offset, 2);
    }
    Settings::evaluationFunctionName = "SPHERE";
    return a;
}

