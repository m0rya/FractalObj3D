//
//  GeometricShapes.h
//  Koch3D
//
//  Created by m0Rya on 2017/04/12.
//
//

#ifndef __Koch3D__GeometricShapes__
#define __Koch3D__GeometricShapes__

#include <stdio.h>
#include <ofMain.h>
#include <makeStl.h>
class GeometricShapes{
private:
    
    
public:
    
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor getColorFromPoint(ofVec3f point, int max);
    
    
};

class Tetrakis : public GeometricShapes{
private:
    float radius;
    void initOrigin();
    vector<ofVec3f> originPoint;
    ofMesh mesh;
    ofVec3f position;
    float raito;
    
    void divideMesh(ofVec3f point[4]);
    void calcRaito();
    
    int numVertices;
    
public:
    
    Tetrakis(float _radius);
    void draw();
    void calcMesh();
    
    //setter getter
    void setRadius(float _radius);
    void setRaito(float _raito);
    
    float getRaito();
    
    
};


class truncatedTetrahedron{
private:
    ofMesh mesh;
    int radius;
    ofVec3f position;
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor makeColorFromPoint(ofVec3f point, int max);
    
    int fineness;
    int itr;
public:
    truncatedTetrahedron(int _radius);
    
    
    void calcMesh();
    void draw();
    
    
    
    //setter
    void setPosition(ofVec3f _position);
    void setRadius(int _radius);
    
    void setFineness(int _fineness);
    void setItr(int _itr);
    
    
    
};


class Triakis{
private:
    //var
    ofVec3f position;
    float radius;
    int mode;   //0: tetra, 1: octa, 2: Icosa
    
    ofMesh mesh;
    vector<ofVec3f> points;
    
    //func
    void initOrigin();
    void makeMesh(ofVec3f point[3]);
    void calcRaito();
    float raito;
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor makeColorFromPoint(ofVec3f point, int max);
    
    vector<ofVec3f> debugNormal;
    vector<ofVec3f> debugOrigin;
    
    
    bool debugOrNot = false;
    
public:
    
    
    Triakis(float _radius);
    void draw();
    void calcMesh();
    
    //setter
    void setPoisiton(ofVec3f _position);
    void setRadius(float _radius);
    void setMode(int _mode);
    void setRaito(float _raito);
    
    //getter
    float getRaito();
    
    
    void debug();
    
};



#endif /* defined(__Koch3D__GeometricShapes__) */
