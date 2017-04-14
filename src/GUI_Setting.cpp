//
//  GUI_Setting.cpp
//  Koch3D
//
//  Created by m0Rya on 2017/03/30.
//
//

#include "GUI_Setting.h"

GUI_Koch3D::GUI_Koch3D(Koch3D &_obj){
    obj = &_obj;
}

GUI_Koch3D::~GUI_Koch3D(){
    delete gui;
}

void GUI_Koch3D::setGUI(){
    gui = new ofxUISuperCanvas("GUI Koch3D", OFX_UI_FONT_MEDIUM);
    vector<string> names;
    names.push_back("0");
    names.push_back("1");
    names.push_back("2");
    names.push_back("3");
    
    gui->addSpacer();
    gui->addLabelButton("Output STL File", false);
    gui->addSpacer();
    gui->addIntSlider("Num of Recursion", 0, 6, numRecursion);
    gui->addSpacer();
    gui->addDropDownList("Differ", names);
    gui->addSpacer();
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_Koch3D::guiEvent);
}

void GUI_Koch3D::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if(name == "Num of Recursion"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setNumRecursion(n->getValue());
    }else if(name == "Differ"){
        ofxUIDropDownList *n = (ofxUIDropDownList *)e.widget;
        vector<ofxUIWidget *> &selected = n->getSelected();
        if(selected.size() == 1){
            obj->setDiffer(ofToInt(selected[0]->getName()));
        }
        
    }else if(name == "Output STL File"){
        obj->outputStlFile();
    }
    
}

void GUI_Koch3D::draw(){
    obj->draw();
}


//=================================================

GUI_pythagorasTree3D::GUI_pythagorasTree3D(pythagorasTree3D &_obj){
    obj = &_obj;
}

GUI_pythagorasTree3D::~GUI_pythagorasTree3D(){
    delete gui;
}

void GUI_pythagorasTree3D::setGUI(){
    gui = new ofxUISuperCanvas("GUI PythagorasTree3D", OFX_UI_FONT_MEDIUM);
    
    gui->addSpacer();
    gui->addLabelButton("Output STL File", false);
    gui->addSpacer();
    gui->addIntSlider("Num of Recursion", 0, 10, numRecursion);
    gui->addSpacer();
    gui->addIntSlider("Angle", 10, 180, angle);
    gui->addSpacer();
    gui->addLabelButton("Random Angle", false);
    gui->addSpacer();
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_pythagorasTree3D::guiEvent);
    
}

void GUI_pythagorasTree3D::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if(name == "Num of Recursion"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setNumRecursion(n->getValue());
    }else if(name == "Angle"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setAngle(n->getValue());
    }else if(name == "Random Angle"){
        obj->setRandomAngle();
        cout << "hello " << endl;
    }else if(name == "Output STL File"){
        obj->outputStl();
    }
}

void GUI_pythagorasTree3D::draw(){
    obj->draw();
}


//===========GUI_Superposition==============
GUI_Superposition::GUI_Superposition(Superposition &_obj){
    obj = &_obj;
}

GUI_Superposition::~GUI_Superposition(){
    delete gui;
}
void GUI_Superposition::setGUI(){
    gui = new ofxUISuperCanvas("GUI Superposition", OFX_UI_FONT_MEDIUM);
    
    gui->addSpacer();
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_Superposition::guiEvent);
}

void GUI_Superposition::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    
}

void GUI_Superposition::draw(){
    obj->draw();
}

//===========GUI_HexFractal==============
GUI_HexFractal::GUI_HexFractal(HexFractal &_obj){
    obj = &_obj;
}

GUI_HexFractal::~GUI_HexFractal(){
    delete gui;
}

void GUI_HexFractal::setGUI(){
    gui = new ofxUISuperCanvas("GUI HexFractal", OFX_UI_FONT_MEDIUM);
    
    vector<string> names;
    for(int i=0; i<2; i++){
        names.push_back(ofToString(i));
    }
    
    gui->addSpacer();
    gui->addIntSlider("Num of Recursion", 1, 10, numRecursion);
    gui->addSpacer();
    gui->addIntSlider("Fineness", 3, 10, fineness);
    gui->addSpacer();
    gui->addIntSlider("Height", 10, 100, height);
    gui->addSpacer();
    gui->addIntSlider("Radius", 10, 200, radius);
    gui->addSpacer();
    gui->addIntSlider("Adding Angle", 0, 180, addingAngle);
    gui->addSpacer();
    gui->addIntSlider("Adding Radius", -20, 20, addingRadius);
    gui->addSpacer();
    gui->addButton("output STL file", false);
    gui->addDropDownList("Mode", names);
    gui->addSpacer();
    
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_HexFractal::guiEvent);
    
}

void GUI_HexFractal::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    
    if(name == "Num of Recursion"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setNumRecursion(n->getValue());
    }else if(name == "Fineness"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setFineness(n->getValue());
    }else if(name == "Height"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setHeight(n->getValue());
    }else if(name == "Radius"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setRadius(n->getValue());
    }else if(name == "output STL file"){
        obj->outputStlFile();
    }else if(name == "Mode"){
        ofxUIDropDownList *n = (ofxUIDropDownList *)e.widget;
        vector<ofxUIWidget *> &selected = n->getSelected();
        if(selected.size() == 1){
            obj->setMode(ofToInt(selected[0]->getName()));
        }       
    }else if(name == "Adding Angle"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setAddingAngle(n->getValue());
        
    }else if(name == "Adding Radius"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setAddingRadius(n->getValue());
    }

}

void GUI_HexFractal::draw(){
    obj->draw();
}



//==========GUI_truncatedTetrahedron==========
GUI_truncatedTetrahedron::GUI_truncatedTetrahedron(truncatedTetrahedron &_obj){
    obj = &_obj;
}

GUI_truncatedTetrahedron::~GUI_truncatedTetrahedron(){
    delete gui;
}
void GUI_truncatedTetrahedron::setGUI(){
    gui = new ofxUISuperCanvas("GUI truncatedTetrahedron", OFX_UI_FONT_MEDIUM);
    
    gui->addSpacer();
    gui->addIntSlider("Radius", 30, 400, radius);
    gui->addSpacer();
    gui->addIntSlider("Fineness", 1, 20, fineness);
    gui->addSpacer();
    gui->addIntSlider("Itr", 0, 20, itr);
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    
    ofAddListener(gui->newGUIEvent, this, &GUI_truncatedTetrahedron::guiEvent);
}

void GUI_truncatedTetrahedron::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if(name == "Radius"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setRadius(n->getValue());
    }else if(name == "Fineness"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setFineness(n->getValue());
    }else if(name == "Itr"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setItr(n->getValue());
    }
    
    
    
}

void GUI_truncatedTetrahedron::draw(){
    obj->draw();
}


//==========GUI_Triakise===================
GUI_Triakis::GUI_Triakis(Triakis &_obj){
    obj = &_obj;
    raito = obj->getRaito();
}

GUI_Triakis::~GUI_Triakis(){
    delete gui;
}

void GUI_Triakis::setGUI(){
    gui = new ofxUISuperCanvas("GUI Triakis", OFX_UI_FONT_MEDIUM);
    
    vector<string> names;
    names.push_back("Triakis Tetrahedron");
    names.push_back("Triakis Octahedron");
    names.push_back("Triakis Icosahedron");
    
    
    gui->addSpacer();
    gui->addIntSlider("Radius", 30, 400, radius);
    gui->addSpacer();
    gui->addSlider("Raito", -2.0, 2.0, raito);
    gui->addSpacer();
    gui->addDropDownList("Mode", names);
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_Triakis::guiEvent);
}

void GUI_Triakis::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if(name == "Radius"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setRadius(n->getValue());
        
    }else if(name == "Mode"){
        ofxUIDropDownList *n = (ofxUIDropDownList *)e.widget;
        vector<ofxUIWidget *> &selected = n->getSelected();
        if(selected.size() == 1){
            
            int _mode;
            string name = selected[0]->getName();
            if(name == "Triakis Tetrahedron"){
                _mode = 0;
            }else if(name == "Triakis Octahedron"){
                _mode = 1;
            }else if(name == "Triakis Icosahedron"){
                _mode = 2;
            }
            
            obj->setMode(_mode);
            raito = obj->getRaito();
        }
    }else if(name == "Raito"){
        ofxUISlider *n = (ofxUISlider *)e.widget;
        obj->setRaito(n->getValue());
    }
}


void GUI_Triakis::draw(){
    obj->draw();
}


//========Tetrakis========

GUI_Tetrakis::GUI_Tetrakis(Tetrakis &_obj){
    obj = &_obj;
    raito = obj->getRaito();
    
}

GUI_Tetrakis::~GUI_Tetrakis(){
    delete gui;
}


void GUI_Tetrakis::setGUI(){
    gui = new ofxUISuperCanvas("GUI Triakis", OFX_UI_FONT_MEDIUM);
    
    
    gui->addSpacer();
    gui->addIntSlider("Radius", 30, 400, radius);
    gui->addSpacer();
    gui->addSlider("Raito", -2.0, 2.0, raito);
    gui->addSpacer();
    
    gui->setTheme(theme);
    gui->setVisible(false);
    gui->autoSizeToFitWidgets();
    
    ofAddListener(gui->newGUIEvent, this, &GUI_Tetrakis::guiEvent);
}

void GUI_Tetrakis::guiEvent(ofxUIEventArgs &e){
    string name = e.widget->getName();
    
    if(name == "Radius"){
        ofxUIIntSlider *n = (ofxUIIntSlider *)e.widget;
        obj->setRadius(n->getValue());
        
    }else if(name == "Raito"){
        ofxUISlider *n = (ofxUISlider *)e.widget;
        obj->setRaito(n->getValue());
    }
}


void GUI_Tetrakis::draw(){
    obj->draw();
}














