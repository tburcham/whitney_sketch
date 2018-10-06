#pragma once


#include "ofMain.h"
#include "ofxGui.h"
#include "ofxBeat.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener {

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
		
        vector<ofColor> colors;
    
        ofxPanel panel;
        ofxFloatSlider xFreq;
        ofxFloatSlider yFreq;
        ofxFloatSlider xWidth;
        ofxFloatSlider yHeight;
    
        ofxFloatSlider speed;
        ofxIntSlider xPos;
        
    
        ofxIntSlider numShapes;
    
        ofxFloatSlider bpm;
    
        bool bHide;
    
        vector<float> timing;
    
        void newMidiMessage(ofxMidiMessage& message);
    ofxMidiIn midiIn;
};
