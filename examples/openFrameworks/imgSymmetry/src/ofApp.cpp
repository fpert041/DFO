/*
 * Click left/right arrows to change the symmetry type
 *
 *
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    s = "7.png";
    //s = "sym_06.jpg";
    
    vis.setup(s);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(!lock){
        vis.draw();
        lock2 = true;
        vis.update();
        lock2 = false;
        
        glPushMatrix();
        ofTranslate(vis.img.getWidth(), 0);
        ofSetColor(0);
        ofDrawBitmapString(o, 5, 130);
        ofSetColor(255);
        glPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(!lock2){
        lock = true;
        
        if (key == 356){ // left
            switcher--;
            switcher = switcher < 0 ? 3 : switcher;
        } else if (key == 358) { // right
            switcher++;
            switcher = switcher > 3 ? 0 : switcher;
        } else if (key == 357) {
            imgNum++;
            imgNum = imgNum > 18 ? 1 :imgNum;
        } else if (key == 359) {
            imgNum--;
            imgNum = imgNum < 1 ? 18 : imgNum;
        } else if (key == 'q') {
            vis.dfo->setDemocracy(true);
        } else if (key == 'w') {
            vis.dfo->setDemocracy(false);
        }
        if (imgNum < 13)
            end = ".png";
        else end = ".jpg";
        
        s = to_string(imgNum) + end;
        
        switch (switcher) {
            case 1:
                vis.setupHori(s);
                o = "Horizontal Symmetry";
                break;
            case 2:
                vis.setupVerti(s);
                o = "Vertical Symmetry";
                break;
            default: // 0
                vis.setup(s);
                o = "2 Ways Symmetry";
                break;
        }
        
        lock = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

