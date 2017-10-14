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
    
    // variable that will hold the DFO algorithm components
    auto_ptr<DFO> dfo;
    
    // draw - sub-methods
    void background();
    
public:
    
    DFOvisual();
    ~DFOvisual();
    
    static const int scaleF = 5;
    
    // DFO & visulaisation environment setup (openFrameworks)
    void setup();
    
    // visualisation (openFrameworks) method
    void draw();

    // run DFO algorithm (update it to + 1 cycle)
    void update();
    
};


#endif /* DFO_visual_hpp */
