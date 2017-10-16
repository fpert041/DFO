//
//  DFO-visual.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 13/10/2017.
//

#include "DFOvisual.hpp"

/* Constructor & Destructor */

DFOvisual::DFOvisual(){
    
    // To test different how the program visualises different fitess funtions
    // Choose which one of these two to comment out
    
    /* EXAMPLE USING THE DEFAULT FITNESS FUNCTION (Sphere test func in this case) */
    dfo.reset( new DFO );
    
    
    /*  EXAMPLE PASSING IN A CUSTOM FITNESS FUNCTION (Ackley test func. in this case) */
//    dfo.reset(
//              new DFO(
//                      [](std::vector<double> p) {
//                          double a = 0;
//                          double b = 0;
//                          for (int i = 0; i < GlobalParam::dim; i++) {
//                              a = a + pow(p[i], 2);
//                              b = b + cos(2 * M_PI * p[i]);
//                          }
//
//                          double c = -20 * exp(-0.2 * sqrt(a / GlobalParam::dim))
//                          - exp(b / GlobalParam::dim) + 20 + M_E;
//                          return c;
//                      }
//                      )
//    );
    
    /*  EXAMPLE PASSING IN ANOTHER CUSTOM FITNESS FUNCTION () */
//    GlobalParam::dim = 2;
//        dfo.reset(
//                  new DFO(
//                          [](std::vector<double> p) {
//                              double x = abs(p[1]);
//                              double y = abs(p[2]);
//                              double fitness_function;
//                              for (int i = 0; i < GlobalParam::dim; i++) {
//                                  fitness_function = 12/x + 18/y * x * y; // x & y are positive
//                              }
//                              return fitness_function;
//                          }
//                          )
//        );
}

DFOvisual::~DFOvisual(){

}

//--------------------------------------------------------------

/* DFO & visulaisation environment setup */

void DFOvisual::setup(){
    
    // OF window setup
    ofSetFrameRate(8);
    
    ofSetWindowShape(GlobalParam::searchSpaceWidth*scaleF, GlobalParam::searchSpaceHeight*scaleF);
    
    dfo->generateSwarm();
}

//--------------------------------------------------------------

void DFOvisual::draw(){
    {
        background();
        
        for(int i = 0; i<GlobalParam::popSize; ++i){
            ofSetColor(255 / GlobalParam::popSize, 255 / GlobalParam::popSize, 255 / GlobalParam::popSize);
            ofSetLineWidth(2);
            
            // draw the axis (i.e. X and Y axis)
            if (true) {
                // in processing it'd be stroke(200, 200, 200, 5);
                ofSetLineWidth((float) 2.5);
                ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight()); // y
                if (GlobalParam::mod_2d)
                    ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2); // x
            }
            
            // ======================= Visualising the flies on the canvas
            // ========================================
            // ========================================
            
            ofPushMatrix();
            
            ofTranslate(GlobalParam::searchSpaceWidth * scaleF / 2, GlobalParam::searchSpaceHeight * scaleF / 2);
            
            // EVERY 2 dimensions together (true) :: EACH dimension separate (false)
            if (GlobalParam::mod_2d) {
                for (int d = 0; d < GlobalParam::dim - 2; d += 2){
                    // for ( int d = 0; d < 1; d++ )
                    int ellipseSize = 5; // ellipse size
                    if (i == GlobalParam::bestIndex) // make the colour of the best particle
                        // RED and twice the size
                    {
                        ofSetColor(255, 0, 0);
                        ellipseSize *= 2;
                    }
                    
                    ofSetLineWidth(0);
                    ofDrawEllipse((float) GlobalParam::swarm[i]->getPos(d) * scaleF / 2,
                                  (float) GlobalParam::swarm[i]->getPos(d + 1) * scaleF / 2, ellipseSize,
                                  ellipseSize);
                    
                    ofSetLineWidth((float) 0.1);
                    ofDrawLine((float) GlobalParam::swarm[i]->getPos(d) * scaleF / 2,
                               (float) GlobalParam::swarm[i]->getPos(d + 1) * scaleF / 2,
                               (float) GlobalParam::swarm[i]->getExPos(d) * scaleF / 2,
                               (float) GlobalParam::swarm[i]->getExPos(d + 1) * scaleF / 2);
                }
            } else {// show each Dimension separately
                
                int gap = ofGetHeight() / (GlobalParam::dim + 1);
                for (int d = 0; d < GlobalParam::dim; d++) {
                    ofSetLineWidth(0.3);
                    
                    // Horizontal Lines
                    int xGap = GlobalParam::searchSpaceWidth * scaleF / 2;
                    int yGap = -GlobalParam::searchSpaceWidth * scaleF / 2 + gap * (d + 1);
                    
                    // flies position
                    int ellipseSize = 5;
                    if (i == GlobalParam::bestIndex) {
                        ofSetColor(255, 0, 0);
                        ellipseSize *= 2;// 5;
                    }
                    ofDrawEllipse((float) GlobalParam::swarm[i]->getPos(d) * scaleF / 2, yGap, ellipseSize, ellipseSize);
                    
                }
                
            }
            
            ofPopMatrix();
            
            // ========================================
            
        }
        
    }
}

//--------------------------------------------------------------

void DFOvisual::update(){
    dfo->updateSwarm();
}


//--------------------------------------------------------------
// PRIVATE HELPER METHODS
//--------------------------------------------------------------
void DFOvisual::background(){
    // clear screen
    ofBackground(255);
    
    // show the summary of the results on the top-left corner
    ofSetColor(255, 255, 255, 150);
    ofDrawRectangle(0, 0, ofGetWidth() / 2 - 5, 80);
    ofSetColor(0);// ,0,0,20);
    ofDrawBitmapString("Dimensions: " + to_string(GlobalParam::dim), 25, 20);
    ofDrawBitmapString("Function: " + GlobalParam::evaluationFunctionName, 25, 35);
    ofDrawBitmapString("Cycles: " + to_string(GlobalParam::evalCount), 25, 50);
    ofDrawBitmapString("Fitness: " + to_string(GlobalParam::swarm[GlobalParam::bestIndex]->getFitness()), 25, 65);
    //text("DT: " + Global.dt, 25, 80);
}
