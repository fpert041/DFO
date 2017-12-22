//
//  DFO-visual.hpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 13/10/2017.
//

#ifndef DFO_visual_hpp
#define DFO_visual_hpp

#include <stdio.h>
#include "DFO.hpp"
#include "ofMain.h"

class DFOvisual {
private:
    static const long serialVersionUID = 1L;
    
    // draw - sub-methods
    void background();
    
    int img_width;
    int img_height;
    
    double bestFitnessOverall = 10E8;
    int bestX, bestY;
    
    int rad = 10; // coverage radius for patch of pixels to test
    int symRange = 200; // maximum pixel range (left/right) to check for symmetry
    int margin = 20;
    
    ofPixels imgPix;
    
public:
    // variable that will hold the DFO algorithm components
    unique_ptr<DFO> dfo = unique_ptr<DFO>(new DFO());
    
    int visualisationHeight;
    int wrapTorus( int n, int threshold );
    double brightness(array<int, 2> p);
    
    DFOvisual();
    ~DFOvisual();
    
    static const int scaleF = 5;
    
    // DFO & visulaisation environment setup (openFrameworks)
    void setup(string s = "1.png");
    void setupVerti(string s = "1.png");
    void setupHori(string s = "1.png");
    
    void dfoSet();
    
    // visualisation (openFrameworks) method
    void draw();

    // run DFO algorithm (update it to + 1 cycle)
    void update();
    
    ofImage img;
    
};


#endif /* DFO_visual_hpp */
