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
    gui->addIntSlider("Num of Recursion", 0, 6, numRecursion);
    gui->addSpacer();
    gui->addDropDownList("Differ", names);
    gui->addSpacer();
    gui->addLabelButton("Output STL File", false);
    
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
    gui->addIntSlider("Num of Recursion", 0, 10, numRecursion);
    gui->addSpacer();
    gui->addIntSlider("Angle", 10, 180, angle);
    gui->addSpacer();
    gui->addLabelButton("Random Angle", false);
    gui->addSpacer();
    gui->addLabelButton("Output STL File", false);
    
    
    
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
    
    gui->addSpacer();
    gui->addIntSlider("Num of Recursion", 1, 10, numRecursion);
    gui->addSpacer();
    gui->addIntSlider("Fineness", 3, 10, fineness);
    gui->addSpacer();
    gui->addIntSlider("Height", 10, 100, height);
    
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
    }

}

void GUI_HexFractal::draw(){
    obj->draw();
}





















