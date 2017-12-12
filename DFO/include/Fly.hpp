//
//  Fly.hpp
//
//  Created by Francesco Perticarari on 10/10/2017.
//
//  THIS CLASS PROVIDES A TEMPLATE FOR CONSTRUCTING FLY/AGENT OBJECTS
//  These objects are the units (indivisuals) that make up the Swarm in DFO (Dispersive Fly Optimisation)
//

#ifndef Fly_hpp
#define Fly_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

#include "GlobalParam.hpp"

class Fly{
    
private:
    std::vector<double>pos; // fly position (in an N-Dimentional problem/search space)
    std::vector<double>exPos; // old position
    double fitness = 10E8; // fitness
    int posDimensions; // variable holding the dimensions of the problem's space
    GlobalParam * pContext = nullptr; // holds a pointer to the swarm we are in and its parameters
    
public:
    
    std::vector<int> leftNindex, rightNindex; // these two values store locally the index position of the left and right neighbours in the global swarm-vector
    // Note: the above parameters are not necessary in all situations as sometimes flies are considered neighbours based merely on their index position (using ring topology)
    
    // =============== Interface Methods =================
    
    
    // Constructors
    Fly(std::vector<double> inPos, GlobalParam& context);
    Fly(std::vector<double> inPos, GlobalParam* context);
    
    const std::vector<double>& getPos(); // get the vector ("of coordinates") of the fly's position (in the search space)
    
    const double getPos(int n); //overloaded function to get the value of a single dimension from the fly's position
    
    const std::vector<double> getExPos(); // get the vector of the previous position ("coordinates")
    
    const double getExPos(int n); //overloaded function to get the value of a single dimension from the fly's old position
    
    void setPos(std::vector<double> position); // set the position of the fly with a vector supplied as argument
 
    void setPos(int n, double inPos); // change one specific dimension (n) of the fly's position to 'inPos'
    
    void setFitness(double t); // set fitness value
    
    const double getFitness(); // return fitness value
    
    // take in the reference of a swarm of flies (vector) and an int 'n'
    // then return the distance between
    const double getDistance(int n);
    
    const std::string toString();
    
    /*
     public String toString() {
     String s = "";
     for (int d = 0; d < 1; d++)
       s.append(std::to_string(pos[d]) ).append(", ");
       s.asspend(pos[posDimensions-1]);
     
     return s;
     }
     */
    
};



#endif /* Fly_hpp */

