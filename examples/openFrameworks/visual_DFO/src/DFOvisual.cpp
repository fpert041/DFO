//
//  DFO-visual.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 13/10/2017.
//

#include "DFOvisual.hpp"

ofImage img;

/* Constructor & Destructor */

DFOvisual::DFOvisual(){
    
    //
    // To test different how the program visualises different fitess funtions
    // Choose which one of these two to comment out
    // //
    
    /* EXAMPLE USING THE DEFAULT FITNESS FUNCTION (Sphere test func in this case) */
    dfo.reset( new DFO );

    visualisationHeight = dfo->getSearchSpaceWidth(0) +  dfo->getDim();
    dfo->setPopSize(20);
    //dfo->setDemocracy(true);
    
    
    /*  EXAMPLE PASSING IN A CUSTOM FITNESS FUNCTION (Ackley test func. in this case) */
//    dfo.reset(
//              new DFO(
//                      [this](std::vector<double> p) {
//                          double a = 0;
//                          double b = 0;
//                          for (int i = 0; i < dfo->dim; i++) {
//                              a = a + pow(p[i], 2);
//                              b = b + cos(2 * M_PI * p[i]);
//                          }
//
//                          double c = -20 * exp(-0.2 * sqrt(a / dfo->dim))
//                          - exp(b / dfo->dim) + 20 + M_E;
//                          return c;
//                      }
//                      )
//    );
    
    /*  EXAMPLE PASSING IN ANOTHER CUSTOM FITNESS FUNCTION () */
//        dfo.reset(
//                  new DFO(
//                          [this](std::vector<double> p) {
//                              double x = abs(p[1]);
//                              double y = abs(p[2]);
//                              double fitness_function;
//                              for (int i = 0; i < dfo->dim; i++) {
//                                  fitness_function = 12/x + 18/y * x * y; // x & y are positive
//                              }
//                              return fitness_function;
//                          }
//                          )
//        );
//    dfo->setDim(2);
    
      /*  EXAMPLE PASSING IN IMG BRIGHNTESS FUNCTION () */
//    mod_2d = true;
//    img.load("/Users/pesa/Documents/UNI/of_v0.9.8_osx_release/apps/naturalComp/wk2_DFO/my_image.png");
//        dfo.reset(
//                      new DFO(
//                              [this](std::vector<double> p) {
//                                  double x = abs(p[0]);
//                                  double y = abs(p[1]);
//                                  ofColor c = img.getColor(x, y); // not sure if in OF the function is actually getBrightness() but you get the idea ;)
//                                  double brightness_of_a_pixel = (double) c.getBrightness();
//                                  double fitness_function_result;
//                                  for (int i = 0; i < dfo->dim; i++) {
//                                      fitness_function_result = 255. - brightness_of_a_pixel;
//                                  }
//                                  return fitness_function_result;
//                              }
//                              )
//            );
//  dfo->dfo->setDim(2);
//  dfo->setSearchSpaceWidth(0, img.getWidth());
//  dfo->setSearchSpaceWidth(0, img.getHeight());
}

DFOvisual::~DFOvisual(){

}

//--------------------------------------------------------------

/* DFO & visulaisation environment setup */

void DFOvisual::setup(){
    
    // OF window setup
    ofSetFrameRate(8);
    
    ofSetWindowShape(dfo->getSearchSpaceWidth(0)*scaleF, visualisationHeight*scaleF);
    
    dfo->generateSwarm();
}

//--------------------------------------------------------------

void DFOvisual::draw(){
    {
        background();
        
        for(int i = 0; i<dfo->getPopSize(); ++i){
            ofSetColor(255 / dfo->getPopSize(), 255 / dfo->getPopSize(), 255 / dfo->getPopSize());
            ofSetLineWidth(2);
            
            // draw the axis (i.e. X and Y axis)
            if (true) {
                // in processing it'd be stroke(200, 200, 200, 5);
                ofSetColor(100);
                ofSetLineWidth((float) 5);
                ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight()); // y
                if (mod_2d)
                    ofDrawLine(0, ofGetHeight() / 2, ofGetWidth(), ofGetHeight() / 2); // x
            }
            ofSetColor(0);
            
            // ======================= Visualising the flies on the canvas
            // ========================================
            // ========================================
            
            ofPushMatrix();
            
            ofTranslate(dfo->getSearchSpaceWidth()[0] * scaleF / 2, visualisationHeight * scaleF / 2);
            
            // (true) Group dimensions in pairs and plot them on a XY graph (as if each was 1 fly)
            // (false) Draw EACH dimension separately and visualise the value for any given fly as a black dot on it
            if (mod_2d) {
                for (int d = 0; d < dfo->getDim() - 2; d += 2){
                    // for ( int d = 0; d < 1; d++ )
                    ofSetColor(0);
                    int ellipseSize = 5; // ellipse size
                    if (i == dfo->getBestIndex()) // make the colour of the best particle
                        // RED and twice the size
                    {
                        ofSetColor(255, 0, 0);
                        ellipseSize *= 2;
                    }
                    
                    ofSetLineWidth(0);
                    ofDrawEllipse((float) dfo->swarm[i]->getPos(d) * scaleF / 2,
                                  (float) dfo->swarm[i]->getPos(d + 1) * scaleF / 2, ellipseSize,
                                  ellipseSize);
                    
                    ofSetLineWidth((float) 0.1);
                    ofDrawLine((float) dfo->swarm[i]->getPos(d) * scaleF / 2,
                               (float) dfo->swarm[i]->getPos(d + 1) * scaleF / 2,
                               (float) dfo->swarm[i]->getExPos(d) * scaleF / 2,
                               (float) dfo->swarm[i]->getExPos(d + 1) * scaleF / 2);
                }
            } else {// show each Dimension separately
                
                int gap = ofGetHeight() / (dfo->getDim() + 1);
                for (int d = 0; d < dfo->getDim(); d++) {
                    ofSetLineWidth(0.3);
                    
                    // Horizontal Lines
                    int xGap = dfo->getSearchSpaceWidth()[0] * scaleF / 2;
                    int yGap = -dfo->getSearchSpaceWidth()[0] * scaleF / 2 + gap * (d + 1);
                    ofSetColor(0);
                    ofDrawLine(-xGap, yGap, xGap, yGap);
                    
                    // flies position
                    int ellipseSize = 5;
                    if (i == dfo->getBestIndex()) {
                        ofSetColor(255, 0, 0);
                        ellipseSize *= 2;// 5;
                    }
                    ofDrawEllipse((float) dfo->swarm[i]->getPos(d) * scaleF / 2, yGap, ellipseSize, ellipseSize);
                    
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
    ofDrawBitmapString("Y: each dimension / X: value || dots = the val. of each dim. per each fly", 55, 10);
    ofDrawBitmapString("Dimensions: " + to_string(dfo->getDim()), 25, 20);
    ofDrawBitmapString("Function: " + dfo->getEvalFuncName(), 25, 35);
    ofDrawBitmapString("Cycles: " + to_string(dfo->getEvalCount()), 25, 50);
    ofDrawBitmapString("Fitness: " + to_string(dfo->getBestFly()->getFitness()), 25, 65);
    ofDrawBitmapString("Best Index: " + to_string(dfo->getBestIndex()), 25, 80);
    ofDrawBitmapString("Best Vector: ", 25, 95);
    for(int i = 0; i<dfo->getDim(); ++i){
        ofDrawBitmapString(to_string(int(dfo->getBestFly()->getPos(i))), 130+i*40, 95);
    }
    //text("DT: " + Global.dt, 25, 80);
}
