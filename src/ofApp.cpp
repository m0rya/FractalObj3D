#include "ofApp.h"

int num_recursion = 3;
RectDivision3D rD(600, 30, 400, num_recursion);
Koch3D koch3d(num_recursion, 300);
makeStl stl("outputFile.stl");
ofVec3f point[3];
ofVec3f lightPos;

pythagorasTree3D pyTree(100, 5, &stl);

Superposition sp(3, 100, 50);

HexFractal hf(5, 100);

truncatedTetrahedron tt(200);

Triakis trks(200);

Tetrakis ttrks(200);

//GUI
int theme = 9;
int drawMode = 3;
GUI_Koch3D gui_koch(koch3d);
GUI_pythagorasTree3D gui_pyTree(pyTree);
GUI_Superposition gui_sp(sp);
GUI_HexFractal gui_hf(hf);
GUI_truncatedTetrahedron gui_tt(tt);
GUI_Triakis gui_trks(trks);
GUI_Tetrakis gui_ttrks(ttrks);

GUIBase *guiArray[] = {&gui_koch, &gui_pyTree, &gui_sp, &gui_hf, &gui_tt, &gui_trks, &gui_ttrks};

ofxUISuperCanvas *fractalList;
ofxUIDropDownList *ddl;


//Picture
ofImage myImage;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackground(0);
    ofEnableDepthTest();
    ofEnableSmoothing();
    
    //lighting
    pointlight.setSpotlight();
    pointlight.setDirectional();
    pointlight.setAmbientColor(ofFloatColor(0.5, 0.2, 0.2, 1.0));
    pointlight.setDiffuseColor(ofFloatColor(.86, .85, .55));
    pointlight.setSpecularColor(ofFloatColor(1.f, 1.f, 1.f));
    
    lightPos = ofVec3f(-40, 60, 600);
    pointlight.setPosition(lightPos);
    pointlight.enable();
    
    
    anotherLight.setDirectional();
    anotherLight.setAmbientColor(ofFloatColor(0.5, 0.2, 0.2, 1.0));
    anotherLight.setDiffuseColor(ofFloatColor(.36, .35, .35));
    anotherLight.setSpecularColor(ofFloatColor(.5f, .5f, .5f));
    anotherLight.setPosition(-1*lightPos);
    anotherLight.enable();
    
    
    //setting for Koch3D
    koch3d.setNoiseForTopPoint(true);
    koch3d.setStlFile(&stl);
    koch3d.setTypeOfObject("octa");
    
    //setting for pythagoras Tree
    pyTree.initRecursion();
    
    //seting for Superposition
    sp.calcMesh();
    //sp.setStlFile(&stl);
    
    //setting for HexFractal
    hf.initRecursion();
    hf.setStlFile(&stl);
    
    //TT
    tt.calcMesh();
    
    
    
    //GUI ddl
    fractalList = new ofxUISuperCanvas("Fractal List");
    fractalList->addSpacer();
    
    vector<string> names;
    names.push_back("Koch3D");
    names.push_back("PythagorasTree3D");
    names.push_back("Superposition");
    names.push_back("HexFractal");
    names.push_back("TruncatedTetrahedron");
    names.push_back("Triakis");
    names.push_back("Tetrakis");
    
    fractalList->setWidgetFontSize(OFX_UI_FONT_SMALL);
    ddl = fractalList->addDropDownList("Fractal List", names);
    ddl->setColorPadded(ofColor(0));
    ddl->setAutoClose(true);
    ddl->setShowCurrentSelected(true);
    fractalList->autoSizeToFitWidgets();
    ofAddListener(fractalList->newGUIEvent, this, &ofApp::guiEvent_ddl);
    fractalList->setVisible(false);
    fractalList->setTheme(theme);
    
    for(int i=0; i<sizeof(guiArray)/sizeof(guiArray[0]); i++){
        guiArray[i]->setGUI();
    }
    
   //exp
    /*
    exp.setup(ofGetWidth(), ofGetHeight(), 24);
    exp.setOutputDir("out");
    exp.setOverwriteSequence(true);
    exp.setAutoExit(true);
    exp.startExport();
     */
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    //exp.begin();
    
    ofBackground(0);
    
    ofEnableDepthTest();
    ofEnableLighting();
    pointlight.enable();
    anotherLight.enable();
    
    cam.begin();
    ofSetColor(ofColor(255));
    ofDrawSphere(lightPos, 10);
    ofDrawSphere(-1*lightPos, 10);
    
    //tree.draw();
    //test.draw();
    //rD.draw();
    if(!guiArray[drawMode]->gui->isEnabled())
        guiArray[drawMode]->gui->enable();
    guiArray[drawMode]->draw();
    //cout << drawMode << endl;
    
    cam.end();
    
    //exp.end();
    //exp.draw(0, 0);

}

//--------------------------------------------------------------
void ofApp::exit(){
    delete fractalList;
}

void ofApp::guiEvent_ddl(ofxUIEventArgs &e){
    string name = e.widget->getName();
    if(name == "Fractal List"){
        ofxUIDropDownList *ddllist = (ofxUIDropDownList *)e.widget;
        vector<ofxUIWidget *> &selected = ddllist->getSelected();
        
        if(selected.size() == 1){
            if(selected[0]->getName() == "Koch3D"){
                guiArray[drawMode]->gui->disable();
                drawMode = 0;
                
            }else if(selected[0]->getName() == "PythagorasTree3D"){
                guiArray[drawMode]->gui->disable();
                drawMode = 1;
            }else if(selected[0]->getName() == "Superposition"){
                guiArray[drawMode]->gui->disable();
                drawMode = 2;
            }else if(selected[0]->getName() == "HexFractal"){
                guiArray[drawMode]->gui->disable();
                drawMode = 3;
            }else if(selected[0]->getName() == "TruncatedTetrahedron"){
                guiArray[drawMode]->gui->disable();
                drawMode = 4;
            }else if(selected[0]->getName() == "Triakis"){
                guiArray[drawMode]->gui->disable();
                drawMode = 5;
            }else if(selected[0]->getName() == "Tetrakis"){
                guiArray[drawMode]->gui->disable();
                drawMode = 6;
            }
        }
    }
}

void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == OF_KEY_UP){
        num_recursion += 1;
        //test.setNumRecursion(num_recursion);
        //rD.setNumRecursion(num_recursion);
        pyTree.setNumRecursion(num_recursion);
    }else if(key == OF_KEY_DOWN){
        num_recursion -= 1;
        //test.setNumRecursion(num_recursion);
        //rD.setNumRecursion(num_recursion);
        pyTree.setNumRecursion(num_recursion);
    }else if(key == 'a'){
        lightPos.x += 20;
    }else if(key == 'z'){
        lightPos.x -= 20;
    }else if(key == 's'){
        lightPos.y += 20;
    }else if(key == 'x'){
        lightPos.y -= 20;
    }else if(key == 'd'){
        lightPos.z += 20;
    }else if(key == 'c'){
        lightPos.z -= 20;
    }else if(key == 'o'){
        koch3d.outputStlFile();
        pyTree.outputStl();
    }else if(key == 't'){
        myImage.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
        myImage.saveImage("./pic/picture.png", OF_IMAGE_QUALITY_BEST);
    }
    pointlight.setPosition(lightPos);
    cout << lightPos << endl;
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(!fractalList->isHit(x, y)){
        fractalList->setVisible(false);
    }
    if(button == 2){
        fractalList->setPosition(x,y);
        fractalList->setVisible(true);
    }
    
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
