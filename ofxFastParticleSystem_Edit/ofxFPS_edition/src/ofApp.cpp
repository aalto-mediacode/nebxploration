//
// NOTE! This test is built on top of the ofxFastParticleSystem addon example "example-StrangeAttractor" made by github user 'fusefactory'. This is work in progress to modify the particle system intoa nebula-like behaviour. This is Licensed under the Apache License, Version 2.0 as stated below.

//  This file is part of the ofxFastParticleSystem [https://github.com/fusefactory/ofxFastParticleSystem]
//  Copyright (C) 2018 Fuse srl
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include "ofApp.h"

float timestep = 0.0001;

float cameraDist        = 15; // Original value 20
float cameraRotation    = 100.0; // Original value 0.0
float rotAmount         = 0.0025; // Original value 0.005

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);
    ofSetFrameRate(60);
    myImg.load("space.jpg"); // image (c) Jeremy Perkins (Pexels.com)

    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    width = ofGetWidth();
    height = ofGetHeight();
    
#if (OF_VERSION_MINOR == 9)
    cam.rotate(-90, ofVec3f(1.0,0.0, 0.0));
#else
    cam.rotateDeg(-90, ofVec3f(1.0,0.0, 0.0));
#endif
    cam.setDistance(cameraDist);

    cam.setNearClip(0.1);
    cam.setFarClip(200000);
    
    fboScreen.allocate(width, height, GL_RGB);
    fboScreen.begin();
    ofClear(0.0);
    fboScreen.end();
    
    // Original values: 2000, 1000, 5
    unsigned w = 1250;
    unsigned h = 750;
    unsigned d = 5;
    
    float* particlesPosns = new float [w * h  * 4];
    particles.init(w, h, ofPrimitiveMode::OF_PRIMITIVE_POINTS, 2);
    
    // random offset for particle's initial position
    // different attractors works better with different starting offset positions
    float startOffset = 10.0;//1.5;
    
    for (unsigned y = 0; y < h; y++){
        for(unsigned x = 0; x < w; x++){
            unsigned idx = y * w + x;
            
            particlesPosns[idx * 4] =    ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +1] = ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +2] = ofRandom(-startOffset, startOffset);
            particlesPosns[idx * 4 +3] = 0;
        }
    }
    
    particles.loadDataTexture(FastParticleSystem::POSITION, particlesPosns);
    delete[] particlesPosns;
   
    particles.zeroDataTexture(FastParticleSystem::VELOCITY);

    particles.addUpdateShader("shaders/updateParticle");
    particles.addDrawShader("shaders/drawParticle");
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    
    cam.lookAt(ofVec3f(0.0, 0.0, 0.0));
    cam.setPosition(cameraDist*sin(cameraRotation),
                    0.0,
                    cameraDist*cos(cameraRotation));
    
    cameraRotation += rotAmount;
    
    timestep = ofMap(ofGetHeight(), 0.0, ofGetWidth(), 0.0001, 0.055);
    ofShader &shader = particles.getUpdateShader();
    shader.begin();
    
    shader.setUniform1f("timestep", timestep);
    
    shader.end();
    
    particles.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(0,0,0,255);
    
    fboScreen.begin();
    ofClear(0, 0, 0);
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);

    myImg.draw(0,0);
    
    
    ofColor gradient1(220,220,220,188);
    ofColor gradient2(22,22,22,10);
    ofBackgroundGradient(gradient1, gradient2, OF_GRADIENT_BAR);
    
    // sizeR values below 5 introduces lagging (this is WIP)
    float mySize=6;
    float scaleX=0.002;
    float scaleY=0.003;
    float time=ofGetElapsedTimef()*0.02;
    

    
    for(int x=0;x<ofGetWidth();x+=mySize){
        for(int y=0;y<ofGetHeight();y+=mySize){
            // play around with the values to get a different pattern and color
            float myColorR=ofNoise(x*scaleX,y*scaleY-50, time)*25;
            float myColorG=ofNoise(x*scaleX*0.5,y*scaleY-50, time)*127;
            float myColorB=ofNoise(x*scaleX*2,y*scaleY-50, time)*127;
            ofSetColor(myColorR,myColorG,myColorB,96);
            ofDrawRectangle(x, y, mySize, mySize);

        }
        
    }
    

    
    cam.begin();
    
    ofShader &shader = particles.getDrawShader();
    shader.begin();
    shader.setUniformMatrix4f("modelViewProjectionMatrix", cam.getModelViewProjectionMatrix());
    shader.end();
    particles.draw();
    ofDisableBlendMode();
    
    cam.end();
    fboScreen.end();
    
    fboScreen.draw(0, 0, width, height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
