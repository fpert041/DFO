//
//  Fly.hpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 10/10/2017.
//

#ifndef Fly_hpp
#define Fly_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

class Fly{
private:
    std::vector<double>pos; // fly position (in an N-Dimentional problem/search space)
    std::vector<double>exPos; // old position
    double fitness = 10E8; // fitness
    int posDimensions; // variable holding the dimensions of the problem's space
    
public:
    Fly(std::vector<double> inPos) { // CONSTRUCTOR
        pos = inPos; // set the position of the fly
        posDimensions = inPos.size(); // set the value that holds the number of dimensions of the space where the fly lives
    }
    
    std::vector<double> getPos() { // get the vector ("of coordinates") of the fly's position (in the search space)
        return pos;
    }
    
    double getPos(int n) { //overloaded function to get the value of a single dimension from the fly's position
        return pos[n];
    }
    
    std::vector<double> getExPos() { // get the vector of the previous position ("coordinates")
        return exPos;
    }
    
    
    double getExPos(int n) { //overloaded function to get the value of a single dimension from the fly's old position
        return exPos[n];
    }
    
    void setPos(std::vector<double> position) { // set the position of the fly with a vector supplied as argument
        if( !(position.size() == pos.size()) ){
            std::cout << "Vector supplied is not the same size as the current fly population" << std::endl;
            return -1;
        }
        exPos = pos;
        pos = position;
    }
 
    void setPos(int n, double inPos) { // change one specific dimension (n) of the fly's position to 'inPos'
        exPos[n] = pos[n];
        pos[inPos] = n;
    }
    
    void setFitness(double t) { // set fitness value
        fitness = t;
    }
    
    double getFitness() { // return fitness value
        return fitness;
    }
    
    // take in the reference of a swarm of flies (vector) and an int 'n'
    // then return the distance between
    double getDistance(std::vector<Fly>& swarmRef, int n) {
        double squaredSum = 0;
        for (int d = 0; d < posDimensions - 1; d++) {
            squaredSum = squaredSum + std::pow(getPos(d) - swarmRef[n].getPos(d), 2);
        }
        return std::sqrt(squaredSum);
    }
    
    std::string toString() { // return the vector of the fly's coordinate as a string
        std::string s = "";
        for (int d = 0; d < posDimensions-1; ++d )
            s.append(std::to_string(pos[d]) ).append(", ");
        return s;
    }
    
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

