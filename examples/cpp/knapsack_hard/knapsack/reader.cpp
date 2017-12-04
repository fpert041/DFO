//
//  reader.cpp
//  knapsack
//
//  Created by Francesco Perticarari on 29/11/2017.
//  Copyright © 2017 agapeSoft. All rights reserved.
//

#include "reader.hpp"
#include <stdexcept>      // std::invalid_argument
#include <array>
#include <math.h>

Reader::Reader(string problemTextPath){
    
    // WHEN READING A FILE AT RUNTIME, THE PATH IS FROM THE APP (e.g. in Build/Products/Debug)
    fstream myfileX(problemTextPath, ios_base::in);
    ifstream myfile(problemTextPath, ifstream::in);
    
    if(!myfile.is_open())
        printf("Could not read file!\n");
    else
        printf("File opened correctly\n");
    
    // Prepare variables and counters to parse the content of the opened file
    std::string str;
    int count = 0;
    array<int, 2> knapAndObj = {INT_MAX, INT_MAX};
    array<int, 2> matrixHelp;
    
    // read line by line until the end of the text document
    while (std::getline(myfile, str)) {
        //std::cout << str << std::endl;  // output the line
        
        // pass each line as string into a stringstream object...
        std::stringstream ss(str);
        istringstream iss(str);
        string word;
        //...and parse each word within the line
        while(iss >> word) {
            /* if the word is actually a number: work out what piece of data it represent in the current problem,
               then store it appropriately into the correct "problem" object
             */
            try {
                std::string::size_type sz;   // alias of size_t
                int i_dec = std::stoi (word, &sz);
                //cout << i_dec << " ";
                if(count < 2) {
                    knapAndObj[count] = i_dec;
                } else if(count < 3){
                    //cout << "num_knaps: " << knapAndObj[0] << " num_obj: " << knapAndObj[1] << " "; // <<<<<<<<<<< CHECK
                    //cout << "\nweights / {knap_capacs} / [k][o]constr:\n"; // <<<<<<<<<<< CHECK
                    problems.back()->weights.push_back(i_dec);
                    problems.back()->nKnaps = knapAndObj[0];
                    problems.back()->nObjects = knapAndObj[1];
                    for(int i = 0; i<knapAndObj[0]; ++i){
                        problems.back()->constraints.push_back(vector<int>(knapAndObj[1], -1));
                    }
                    matrixHelp[0] = 2+knapAndObj[1]+knapAndObj[0];
                    matrixHelp[1] = 2+knapAndObj[1]+knapAndObj[0]+knapAndObj[0]*knapAndObj[1];
                    //cout << i_dec << " "; // <<<<<<<<<<< CHECK
 
                } else if (count < 2+knapAndObj[1]){
                    problems.back()->weights.push_back(i_dec);
                    //cout << i_dec << " "; // <<<<<<<<<<< CHECK
                } else if (count < matrixHelp[0]) {
                    problems.back()->capacs.push_back(i_dec);
                    //cout << "{"<< i_dec << "} "; // <<<<<<<<<<< CHECK
                } else if (count < matrixHelp[1]){
                    int temp = count-matrixHelp[0];
                    int knapLoc = floor(temp)/knapAndObj[1];
                    int constLoc = temp-(int)knapLoc*knapAndObj[1];
                    problems.back()->constraints[knapLoc][constLoc] = i_dec;
                    //cout << "["<< knapLoc << "][" << constLoc << "](" <<i_dec << ") "; // <<<<<<<<<<< CHECK
                } else {
                    problems.back()->optimalWeight = i_dec;
                    //cout << "\noptimal weight: " << i_dec << " \n"; // <<<<<<<<<<< CHECK
                }
                count ++;
            }
            /* if the word is NOT a number: then check if it is "problem" - if so, generate a new problem object
                and give it an ID based on the word that comes after the "problem" flag, then reset the counter,
                and get ready to receive the sequence of numbers that define the problem
             */
            catch (const std::invalid_argument& ia) {
                //std::cerr << "Invalid argument: " << ia.what() << '\n';
                if(word == "problem"){
                    count = 0;
                    string name;
                    iss >> name;
                    problems.push_back(new Problem(name));
                    //cout << "\nprob ID: " << problems[problems.size()-1]->probID ; // // <<<<<<<<<<< CHECK
                    //cout << endl; // // <<<<<<<<<<< CHECK
                }
            }
        }
    }
    
    printf("Problems within the text file loaded successfully!\n");
    cout << "Problems Loaded: " << problems.size() << endl;
}

Reader::~Reader(){
    // free memory and distroy pointer
    while(!problems.empty()){
        if(!(problems.back()==nullptr))
            delete problems.back();
        problems.pop_back();
    }
}
