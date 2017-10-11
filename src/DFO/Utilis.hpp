//
//  Utilis.hpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 11/10/2017.
//

#ifndef Utilis_hpp
#define Utilis_hpp

#include <stdio.h>
#include <random>

#include "Settings.hpp"
#include "Fly.hpp"

using namespace std;

class Utilis {
private:
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis;  // Each call to dis(gen) will generates a new random double
    
    Utilis(); // CONSTRUCTOR (defined in cpp)
    
    double ran; // random number set when an object of this type is initialise
    
    // This enumerator below is used by evaluate() to choose which method to use in the evaluation of a Fly's position vector - the ones available are: Sphere Schwefel12 Rosenbrock GSchwefel26 Rastrigin Ackley Griewank PenalizedP8 PenalizedP16
    enum EvaluationMethod { SPHERE, SCHWEFEL12, ROSENBROCK, GSCHWEFEL26, RASTRIGN, ACKLEY, GRIEWANK, PENALIZEDP8, PENALISEDP16 };
    EvaluationMethod em;
    
    enum NeighbouringTopologyType { RING, RANDOM };
    NeighbouringTopologyType ntt;
    
    double offset = -0;
    int dimensions;
    
    double eval_sphere(std::vector<double>); // evaluate the fitness of a fly using the Sphere "benchmark function"
    
    // ********************* INTERFACE *********************
    
public:
    // ===================== variables =====================
    
    // ===================== functions =====================
    
    double evaluate(vector<double> flyPos); // Evaluate the fitness of a certain Fly
    
    void findClosestNeighbours(int flyIndex); // find the 2 closest neighbours for the fly at the index supplied
    void findClosestNeighbours(int flyIndex, Fly& flyRef); // overloaded function that stores neighbours' information into each fly
    
    void getRandF_or_RingT_Neighbours(int curr, bool topology); //Set the closest 2 neighbours in the swarm for the fly at location 'curr' using either RING TOPOLOGY or RANDOMNESS (use 0 or 1)
    void getRandF_or_RingT_Neighbours(int curr, bool topology, Fly& flyref); // overloaded function that stores neighbours' information into each fly
    
    void shakeOffset(); // move offset by a random value between -10 and 10
    
    void findBestFly(); // find the fly whose position is the current best solution to our problem (fittest)
    
    void printSummary(); // Print to console summary of the findings of the algorithm
    
    
    
    
    
    
    // TODO: Implement the following evaluation methods -> Schwefel12 Rosenbrock GSchwefel26 Rastrigin Ackley Griewank PenalizedP8 PenalizedP16 // Once you do this, add their calls into the cases of evaluate()
};

#endif /* Utilis_hpp */
