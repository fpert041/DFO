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
#include <functional>
#include "Fly.hpp"

using namespace std;

class Utilis : public GlobalParam {
private:
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen; //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis;  // Each call to dis(gen) will generates a new random double
    
    double ran; // random number set when an object of this type is initialise
    
    double offset = -0;
    
    std::function<double(std::vector<double>)> eval_custom_fitness_func; // empty function storage variable -> it will be used if a fitness function is provided externally
    
    double eval_sphere(std::vector<double>&); // evaluate the fitness of a fly using the Sphere "benchmark function"
    
    // ********************* INTERFACE *********************
    
public:
    // ===================== variables/types =====================
    
    // This enumerator below is used by evaluate() to choose which method to use in the evaluation of a Fly's position vector - the ones available are: Sphere Schwefel12 Rosenbrock GSchwefel26 Rastrigin Ackley Griewank PenalizedP8 PenalizedP16
    enum EvaluationMethod { CUSTOM, SPHERE }; //, SCHWEFEL12, ROSENBROCK, GSCHWEFEL26, RASTRIGN, ACKLEY, GRIEWANK, PENALIZEDP8, PENALISEDP16 };
    EvaluationMethod em;
    
    // The below enumerator is usedin choosing which type of default (non-distance based) ineighbouring conection to choose
    enum NeighbouringTopologyType { RING, RANDOM };
    
    NeighbouringTopologyType ntt; // (ntt = neighbour topology type)
    
    // ===================== functions =====================
    
    Utilis(); // CONSTRUCTOR (defined in cpp) -> default evaluation function ==> 'sphere' eval. func is the default method of fitness evaluation
    Utilis(std::function<double(std::vector<double>)> fitness_func); // OVERRIDDEN CONSTRUCTOR -- If we pass in a fitness function as an argument, this will become the default evaluation method for a Fly's fitness
    
    void setFitnessFunc(std::function<double(std::vector<double>)>); // set custom fitness function
    
    void resetFitnessFunc(); // reset fitness function to "sphere" benchmark test
    
    void setNeighbourTopology(NeighbouringTopologyType nt = Utilis::RING); // set the neighbouring topology

    // ********************* ONLY FOR CHILDREN *********************
    
protected:
    
    double evaluate(vector<double> flyPos); // Evaluate the fitness of a certain Fly using the DEFAULT fitness function (indicated by the value of the 'em' varable (enum: EvaluationMethod)
    double evaluate(vector<double> flyPos, EvaluationMethod fit_func_id); // Overridden method: Evaluate the fitness of a certain Fly using the PROVIDED fitness function
    
    void findClosestNeighbours(int flyIndex); // find the 2 closest neighbours for the fly at the index supplied
    void findClosestNeighbours(int flyIndex, Fly& flyRef); // overloaded function that stores neighbours' information into each fly
    
    void getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type); //Set the closest 2 neighbours in the swarm for the fly at location 'curr' using either RING TOPOLOGY or RANDOMNESS (use provided enum)
    void getRandF_or_RingT_Neighbours(int curr, NeighbouringTopologyType type, Fly& flyref); // overloaded function that stores neighbours' information into each fly
    
    void shakeOffset(); // move offset by a random value between -10 and 10
    
    void findBestFly(); // find the fly whose position is the current best solution to our problem (fittest)
    
    void printSummary(); // Print to console summary of the findings of the algorithm
    
    vector<double> genRandPos(); // Generate and return a random Fly's position vector
    
    vector<double> genRandPos2(); // Alternative version of the method above
    
    vector<double> genRandPosPositive(); // Alternative version of the method above, where the search space is only positive
    
    double random(double from, double to); // Output random number (normal distribution) between '1st arg' and '2nd arg'
    double random(double to);// averloaded method, so that if no 2nd arg is pecified it'll be between 0 and the arg passed in
    
    double genGaussian(double bellMean, double bellStdDev); // Given the distribution mean value and its standard deviation (variance), generate and return a Gaussian Random number
    
    
    // TODO: Implement the following evaluation methods -> Schwefel12 Rosenbrock GSchwefel26 Rastrigin Ackley Griewank PenalizedP8 PenalizedP16 // Once you do this, add their calls into the cases of evaluate()
};

#endif /* Utilis_hpp */
