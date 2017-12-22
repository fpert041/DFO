#pragma once

#include "ofMain.h"
#include "imgSymmetry.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    DFOvisual vis;
    int switcher = 0;
    int imgNum = 1;
    string s = "1.png";
    string end = ".png";
    string o = "2 Ways Symmetry";
    bool lock = false;
    bool lock2 = false;
};
