//
//  HexFractal.h
//  Koch3D
//
//  Created by m0Rya on 2017/04/07.
//
//

#ifndef __Koch3D__HexFractal__
#define __Koch3D__HexFractal__

#include <stdio.h>
#include <ofMain.h>
#include <makeStl.h>


class HexFractal{
private:
    ofVec3f center;
    float radius;
    int fineness;
    int numRecursion;
    float height;
    int mode = 0;
    
    float differForAngle = 0;
    float addingAngle = 10;
    
    float differForRadius = 0;
    float addingRadius = 0;
    
    float addingY = 0;
    
    bool outputStl = false;
    
    makeStl* stl;
    
    ofMesh mesh;
    vector<ofVec3f> point;
    vector<ofVec3f> newPoint;
    
    //void recursion(ofVec3f point[6], int n);
    void recursion(vector<ofVec3f> point, int n);
    //void closeMesh(ofVec3f point[6]);
    void closeMesh(vector<ofVec3f> point);
    ofColor makeColorFromPoint(ofVec3f point, int max=500);
    void clear();
    
    
public:
    HexFractal(int _numRecursion, float _radius);
    void draw();
    void initRecursion();
    void outputStlFile();
    
    
    //setter
    void setNumRecursion(int n);
    void setFineness(int n);
    void setHeight(float _height);
    void setRadius(float _radius);
    void setStlFile(makeStl* _stl);
    void setMode(int _mode);
    void setAddingAngle(float _addingAngle);
    void setAddingRadius(float _addingRadius);
    void setAddingY(float _addingY);
    
};

#endif /* defined(__Koch3D__HexFractal__) */
