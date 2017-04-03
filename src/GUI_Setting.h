//
//  GUI_Setting.h
//  Koch3D
//
//  Created by m0Rya on 2017/03/30.
//
//

#ifndef __Koch3D__GUI_Setting__
#define __Koch3D__GUI_Setting__

#include <stdio.h>
#include "GUI_Setting.h"
#include "ofMain.h"

#include "Koch3D.h"
#include "RectDivision3D.h"
#include "pythagorasTree3D.hpp"

#include "ofxUI.h"

class GUIBase{
public:
    ofxUISuperCanvas *gui;
    virtual void guiEvent(ofxUIEventArgs &e) = 0;
    virtual void setGUI() = 0;
    virtual void draw() = 0;
};

class GUI_Koch3D : public GUIBase{
public:
    GUI_Koch3D(Koch3D &_obj);
    ~GUI_Koch3D();
    
    Koch3D *obj;
    float numRecursion = 3;
    int theme = 9;
    
    void setGUI();
    void guiEvent(ofxUIEventArgs &e);
    void draw();
};

class GUI_pythagorasTree3D : public GUIBase{
public:
    GUI_pythagorasTree3D(pythagorasTree3D &_obj);
    ~GUI_pythagorasTree3D();
    
    pythagorasTree3D *obj;
    float numRecursion = 3;
    float angle = 60;
    int theme = 9;
    
    void setGUI();
    void guiEvent(ofxUIEventArgs &e);
    void draw();
};
#endif /* defined(__Koch3D__GUI_Setting__) */
