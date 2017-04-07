//
//  Superposition.h
//  Koch3D
//
//  Created by m0Rya on 2017/04/07.
//
//

#ifndef __Koch3D__Superposition__
#define __Koch3D__Superposition__

#include <stdio.h>
#include <ofMain.h>

class Superposition{
private:
    int fineness;
    int height;
    float radius;
    ofVec3f center;
    ofMesh mesh;
    
    
    void transitRadius();
    vector<ofVec3f> calcCircle(ofVec3f center, float r);
    void makeMeshFrom2Circles(vector<ofVec3f> circle0, vector<ofVec3f> circle1);
    void closeCircle(ofVec3f center, vector<ofVec3f> circle);
    float alterRadius(int i);
    
public:
    
    Superposition(int _fineness, int _height, float _radius);
    
    void calcMesh();
    
    void draw();
};
#endif /* defined(__Koch3D__Superposition__) */
