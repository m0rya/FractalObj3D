#pragma once

#include "ofMain.h"
#include "Koch3D.h"
#include "RectDivision3D.h"
#include "pythagorasTree3D.hpp"
#include "makeStl.h"
#include "GUI_Setting.h"
#include "ofxExportImageSequence.h"
#include "Superposition.h"
#include "HexFractal.h"


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
    
    void guiEvent_ddl(ofxUIEventArgs &e);
    void exit();
    
    ofEasyCam cam;
    ofLight pointlight;
    ofxExportImageSequence exp;
    
    
    
};
