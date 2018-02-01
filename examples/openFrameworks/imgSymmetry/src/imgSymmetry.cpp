//
//  DFO-visual.cpp
//  wk2_DFO
//
//  Created by Francesco Perticarari on 13/10/2017.
//

#include "imgSymmetry.hpp"


/* Constructor & Destructor */

DFOvisual::DFOvisual(){
    
    /* FIND SYMMETRY IN AN IMG */
    /* Uses BRIGHNTESS FINDING FUNCTION () */
    dfo->setDim(2); // searching through an imge ==> 2D space = 2 dimensions
    dfo->setConstrainPos(true); // only search for positive values
}

DFOvisual::~DFOvisual(){
    
}

//--------------------------------------------------------------

/* DFO & visulaisation environment setup */

void DFOvisual::setup(string s){
    img.load(s);
    dfoSet();
    dfo->setFitnessFunc(
                        [this](std::vector<double>& p) {
                            double a = 0;
                            margin = 40;
                            // avoid getting too close to the corners
                            if (p[0]<margin || p[0]>img_width-margin || p[1]<margin || p[1]>img_height-margin){
                                a = 10E8;
                            } else {
                                
                                rad = 50; // coverage radius for patch of pixels to test
                                symRange = 400; // maximum pixel range (left/right) to check for symmetry
                                
                                int x = (int)p[0]+0.5;
                                int y = (int)p[1]+0.5;
                                
                                int x1, x2, y1, y2;
                                int maxX, maxY;
                                int randX, randY;
                                
                                maxX = symRange > img_width ? img_width : symRange;
                                maxY = symRange > img_height ? img_height : symRange;
                                
                                randX = int(ofRandom(maxX+0.5));
                                randY = int(ofRandom(maxY+0.5));
                                
                                // Use torus function to calculate the value of x1 and x2
                                x1 = wrapTorus(x + randX, img_width);
                                x2 = wrapTorus(x - randX, img_width);
                                
                                // Use torus function again to calculate the value of y1 and y2
                                y1 = wrapTorus(y + randY, img_height);
                                y2 = wrapTorus(y - randY, img_height);
                                
                                int sum1 = 0;
                                array<int, 2> newA;
                                // Calculate the value of sum1 here
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { wrapTorus(x1+i, maxX), wrapTorus(y1+j, maxY) };
                                        sum1 += brightness(newA);
                                    }
                                
                                int sum2 = 0;
                                // Calculate the value of sum2 here
                                // ...
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { wrapTorus(x2-i, maxX), wrapTorus(y2-j, maxY) };
                                        sum2 += brightness(newA);
                                    }
                                
                                a = abs( sum1 - sum2 );
                            }
                            
                            return a;
                        }
                        );
}

void DFOvisual::setupVerti(string s){
    img.load(s);
    dfoSet();
    dfo->setFitnessFunc(
                        [this](std::vector<double>& p) {
                            double a = 0;
                            margin = 40;
                            // avoid getting too close to the corners
                            if (p[0]<margin || p[0]>img_width-margin || p[1]<margin || p[1]>img_height-margin){
                                a = 10E8;
                            } else {
                                
                                rad = 50; // coverage radius for patch of pixels to test
                                symRange = 400; // maximum pixel range (left/right) to check for symmetry
                                
                                int x = (int)p[0]+0.5;
                                int y = (int)p[1]+0.5;
                                
                                int x1, x2, y1, y2;
                                int maxX, maxY;
                                int randX, randY;
                                
                                maxX = symRange > img_width ? img_width : symRange;
                                maxY = symRange > img_height ? img_height : symRange;
                                
                                randX = int(ofRandom(maxX+0.5));
                                randY = int(ofRandom(maxY+0.5));
                                
                                // Use torus function to calculate the value of x1 and x2
                                x1 = wrapTorus(x + randX, img_width);
                                x2 = wrapTorus(x - randX, img_width);
                                
                                // Use torus function again to calculate the value of y1 and y2
                                y1 = wrapTorus(y + randY, img_height);
                                y2 = wrapTorus(y - randY, img_height);
                                
                                int sum1 = 0;
                                array<int, 2> newA;
                                // Calculate the value of sum1 here
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { x+i, wrapTorus(y1+j, maxY) };
                                        sum1 += brightness(newA);
                                    }
                                
                                int sum2 = 0;
                                // Calculate the value of sum2 here
                                // ...
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { x-i, wrapTorus(y2-j, maxY) };
                                        sum2 += brightness(newA);
                                    }
                                
                                a = abs( sum1 - sum2 );
                            }
                            
                            return a;
                        }
                        );
}

void DFOvisual::setupHori(string s){
    img.load(s);
    dfoSet();
    dfo->setFitnessFunc(
                        [this](std::vector<double>& p) {
                            double a = 0;
                            margin = 40;
                            // avoid getting too close to the corners
                            if (p[0]<margin || p[0]>img_width-margin || p[1]<margin || p[1]>img_height-margin){
                                a = 10E8;
                            } else {
                                
                                rad = 50; // coverage radius for patch of pixels to test
                                symRange = 400; // maximum pixel range (left/right) to check for symmetry
                                
                                int x = (int)p[0]+0.5;
                                int y = (int)p[1]+0.5;
                                
                                int x1, x2, y1, y2;
                                int maxX, maxY;
                                int randX, randY;
                                
                                maxX = symRange > img_width ? img_width : symRange;
                                maxY = symRange > img_height ? img_height : symRange;
                                
                                randX = int(ofRandom(maxX+0.5));
                                randY = int(ofRandom(maxY+0.5));
                                
                                // Use torus function to calculate the value of x1 and x2
                                x1 = wrapTorus(x + randX, img_width);
                                x2 = wrapTorus(x - randX, img_width);
                                
                                // Use torus function again to calculate the value of y1 and y2
                                y1 = wrapTorus(y + randY, img_height);
                                y2 = wrapTorus(y - randY, img_height);
                                
                                int sum1 = 0;
                                array<int, 2> newA;
                                // Calculate the value of sum1 here
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { wrapTorus(x1+i, maxX), y+j };
                                        sum1 += brightness(newA);
                                    }
                                
                                int sum2 = 0;
                                // Calculate the value of sum2 here
                                // ...
                                for(int i = 0; i<rad; i++)
                                    for(int j=0; j<rad; j++){
                                        newA = { wrapTorus(x2-i, maxX), y-j };
                                        sum2 += brightness(newA);
                                    }
                                
                                a = abs( sum1 - sum2 );
                            }
                            
                            return a;
                        }
                        );
}

//--------------------------------------------------------------

void DFOvisual::draw(){
    
    background();
    
    for(int i = 0; i<dfo->getPopSize(); ++i){
        ofSetColor(255 / dfo->getPopSize(), 255 / dfo->getPopSize(), 255 / dfo->getPopSize());
        ofSetLineWidth(2);
        
        ofSetColor(0);
        
        // (true) Group dimensions in pairs and plot them on a XY graph (as if each was 1 fly)
        // (false) Draw EACH dimension separately and visualise the value for any given fly as a black dot on it
        
        for (int d = 0; d < dfo->getDim() - 1; d += 2){
            // for ( int d = 0; d < 1; d++ )
            ofSetColor(120);
            float pos1 = (float) dfo->swarm[i]->getPos(d);
            float pos2 = (float) dfo->swarm[i]->getPos(d + 1);
            double fit = 0;
            int ellipseSize = 4; // ellipse size
            if (i == dfo->getBestIndex()) // make the colour of the best particle
                // RED and twice the size
            {
                ellipseSize *= 2;
                fit = dfo->swarm[i]->getFitness();
                if(fit < bestFitnessOverall){
                    bestX = pos1;
                    bestY = pos2;
                    bestFitnessOverall = fit;
                }
                ofSetColor(255, 255, 0);
                ofDrawEllipse(bestX, bestY, ellipseSize+1, ellipseSize+1);
                ofSetColor(255, 0, 0);
            }
            
            ofSetLineWidth(0);
            ofDrawEllipse(pos1, pos2, ellipseSize, ellipseSize);
            
            ofSetColor(120, 120, 120, 120);
            if (i == dfo->getBestIndex()) // make the colour of the best particle
                // RED and twice the size
                ofSetColor(255, 0, 0, 120);
            
            ofSetLineWidth(0.1);
            ofDrawLine(pos1, pos2,
                       (float) dfo->swarm[i]->getExPos(d),
                       (float) dfo->swarm[i]->getExPos(d + 1));
            ofSetColor(255);
            
        }
    }
}

//--------------------------------------------------------------

void DFOvisual::update(){
    dfo->updateSwarm();
}


//--------------------------------------------------------------

void DFOvisual::background(){
    // clear screen
    img.draw(0, 0);
    
    glPushMatrix();
    ofTranslate(img.getWidth(), 0);
    
    // show the summary of the results on the top-left corner
    ofSetColor(255, 255, 255, 150);
    ofDrawRectangle(0, 0, ofGetWidth() - 10, 140);
    ofSetColor(0);
    ofDrawBitmapString("Dots: value of each fly's pair of dim.", 5, 10);
    ofDrawBitmapString("Dimensions: " + to_string(dfo->getDim()), 5, 25);
    ofDrawBitmapString("Function: " + dfo->getEvalFuncName(), 5, 40);
    ofDrawBitmapString("Cycles: " + to_string(dfo->getEvalCount()), 5, 55);
    ofDrawBitmapString("Fitness: " + to_string(dfo->getBestFly()->getFitness()), 5, 70);
    ofDrawBitmapString("Best Index: " + to_string(dfo->getBestIndex()), 5, 85);
    ofDrawBitmapString("Best Vector: ", 5, 100);
    for(int i = 0; i<dfo->getDim(); ++i){
        ofDrawBitmapString(to_string(int(dfo->getBestFly()->getPos(i))), 130+i*40, 100);
    }
    if(dfo->getDemocracy())
        ofDrawBitmapString("Algo type: Best Neighbour", 5, 115);
    else
        ofDrawBitmapString("Algo type: Swarm Best", 5, 115);
    
    glPopMatrix();
}

int DFOvisual::wrapTorus( int n, int threshold )
{
    int result = n;
    if ( n >= threshold )
        result = n % threshold;
    else if ( n < 0 )
        result = threshold-n;
    
    return result;
}

double DFOvisual::brightness(array<int, 2> p) {
    if(p[0] < img.getWidth() && p[1] < img.getHeight()){
        return 255 - imgPix.getColor(p[0], p[1]).getBrightness();
    }
}

void DFOvisual::dfoSet(){
    imgPix = img.getPixels();
    
    dfo->setSearchSpaceWidth(0, img.getWidth()-1);
    dfo->setSearchSpaceWidth(1, img.getHeight()-1);
    
    img_width = dfo->getSearchSpaceWidth(0);
    img_height = dfo->getSearchSpaceWidth(1);
    
    // OF window setup
    ofSetFrameRate(10);
    ofSetWindowShape(dfo->getSearchSpaceWidth(0)+400, dfo->getSearchSpaceWidth(1));
    
    dfo->setPopSize(50);
    //dfo->setDemocracy(true);
    
    dfo->generateSwarmPositiveAxis();
}


