#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofLog() << "GL Version" << glGetString( GL_VERSION );
    
    midiIn.listInPorts();
    midiIn.openPort(0);
    midiIn.addListener(this);
    
    //ofSetFullscreen(true);
    //ofEnable
    
    ofSeedRandom(1000);
    
    colors.resize(5);
    colors[0].set(127, 0, 0);
    colors[1] = ofColor::hotPink;
    colors[2] = ofColor::yellow;
    colors[3] = ofColor::purple;
    colors[4] = ofColor:: pink;
    
    panel.setup("", "settings.xml", 10, 100);
    //panel.setup();
    
    panel.add(xFreq.setup("x frequency", 2.7, 0, 5));
    panel.add(yFreq.setup("y frequency", 0.7, 0, 5));
    panel.add(xWidth.setup("x width", 20, 0, 600));
    panel.add(yHeight.setup("y height", 10, 0, 1000));
    panel.add(speed.setup("speed", 0.2, 0, 10));
    
    panel.add(numShapes.setup("numShapes", 20, 1, 100));
    panel.add(xPos.setup("x position", 10, 1, 100));
    
    panel.add(bpm.setup("bpm", 111, 50, 200));
    
    panel.loadFromFile("settings.xml");

    
    for (int i = 0; i < numShapes; i++) {
        timing.push_back(i * (bpm/60.0)); // bpm based pause
    }
    
    //ofSetVerticalSync(true);
    //ofSetFrameRate(24);
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetBackgroundColor(0, 0, 0);
    ofSetLineWidth(5);
    
    //ofTranslate(0, 0);
    ofSetColor(255, 255, 255);
    if (!bHide) {
        panel.draw();
       // ofDisableDepthTest();
    } else {
        //ofEnableDepthTest();
    }
    
    int lineLength = 150;
    
    for (int j = 0; j < numShapes; j++) {
        
        if (ofGetElapsedTimef() >= timing[j] && ofGetElapsedTimef() <= timing[j] + 60) { // 60 seconds on the screen
            // (fmod(ofGetElapsedTimef(), 30.0)
        
            ofPushMatrix();
            
            ofTranslate((j * xPos) % ofGetWidth(), 0);
            //cout << ((j * 10) % ofGetWidth()) << endl;
        
            for (int i = 0; i < 40; i++) {
                
                float finalSpeed = speed * ((0.01 * sin(ofGetElapsedTimef() - timing[j]))+ 0.02);
                
                float offset = i * sin(ofGetElapsedTimef() * finalSpeed);
                
                float x = xWidth * cos((ofGetElapsedTimef() + offset * (PI*2/3.0))* xFreq);
                float y = (ofGetHeight() / 2) - (lineLength / 2) + yHeight * sin((ofGetElapsedTimef() + offset * (PI*2/3.0)) * yFreq);
                
                
                
                /*float x = 10 * cos(ofGetElapsedTimef() * (PI*2/3.0) + j) + 100;
                float y = 10 * sin(ofGetElapsedTimef() * (PI*2/3.0) + j) + 200;*/
                
                /*float size = 300 * sin(ofGetElapsedTimef() - timing[j]);
                
                float offset = sin(ofGetElapsedTimef()) * 2;
                
                float x = xFreq * (cos(ofGetElapsedTimef() - timing[j] + offset * (PI*2/6.0)) * size * (xWidth / 100)) + 100;
                float y = yFreq * (sin(ofGetElapsedTimef() - timing[j] + offset * (PI*2/6.0)) * size * (yHeight / 100)) + 200;*/
                

                ofSetColor(colors[j % 5], 95);
                ofDrawLine(x, y, x, y + lineLength);
                
            }
            
            ofPopMatrix();
            
        }
    }
    
    
    
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& message) {
    
    switch(message.control) {
        case 21:
            xFreq = ofMap(message.value, 0, 127, xFreq.getMin(), xFreq.getMax());
            break;
        case 22:
            yFreq = ofMap(message.value, 0, 127, yFreq.getMin(), yFreq.getMax());
            break;
        case 23:
            xWidth = ofMap(message.value, 0, 127, xWidth.getMin(), xWidth.getMax());
            break;
        case 24:
            yHeight = ofMap(message.value, 0, 127, yHeight.getMin(), yHeight.getMax());
            break;
        case 25:
            speed = ofMap(message.value, 0, 127, speed.getMin(), speed.getMax());
            break;
        case 26:
            numShapes = ofMap(message.value, 0, 127, numShapes.getMin(), numShapes.getMax());
            break;
        default:
            cout << message.control << " not assigned" << endl;
            
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'h'){
        bHide = !bHide;
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
