//
//  pythagorasTree3D.hpp
//  Koch3D
//
//  Created by m0Rya on 2017/03/29.
//
//

#ifndef pythagorasTree3D_hpp
#define pythagorasTree3D_hpp

#include <stdio.h>
#include <ofMain.h>
#include "makeStl.h"

class pythagorasTree3D{
private:
    makeStl* stl;
    ofMesh mesh;
    int angle = 60;
    bool writeStl = false;
    
    void addTriPrism(ofVec3f point[6], int n);
    void addCube(ofVec3f point[4], ofVec3f upPoint[4], int n);
    
    ofVec3f position[4];
    int recursionNum;
    int width;
    bool drawWireframe = false;
    void recursion(ofVec3f point[4], int n);
    ofColor makeColorFromPoint(ofVec3f point);
    
    ofVec3f getNormal(ofVec3f point[3]);
    
    
    //Animation
    int modeForAnime = 0;
    int counterForStop = 0;
    int recursionTrans = 1;
    
    
public:
    
    pythagorasTree3D(int _recursionNum, makeStl* _stl);
    pythagorasTree3D(int _width, int _recursionNum, makeStl* _stl);
    pythagorasTree3D(ofVec3f _position, int _width, int _recursionNum, makeStl* _stl);
    
    void draw();
    void outputStl();
    void initRecursion();
    
    
    void debugNormal();

    
    //setter
    void setNumRecursion(int num);
    void setPosition(ofVec3f _position);
    void setWidth(int _width);
    void setWireframe(bool _drawWireframe);
    void setOutputStl(bool _write);
    void setAngle(int _angle);
    void setRandomAngle();

    void animation();
    
};

#endif /* pythagorasTree3D_hpp */
