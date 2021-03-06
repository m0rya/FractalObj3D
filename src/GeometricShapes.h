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
    ofMesh mesh;
    makeStl *stl;
    string name;
    float radius;
    float height;
    
    void setStl(makeStl *_stl);
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor getColorFromPoint(ofVec3f point, int max);
    ofVec3f getCenterOfGravity(vector<ofVec3f> &point, float height);
    void triInTri(ofVec3f outPoint[3], float raito, int rotate, int n);
    void hexInHex(ofVec3f outPoint[6], float raito, float heightForHexInHex, int n);
    void outputStl();
    
    
    //make mesh like triakis, tetrakis
    void KisMesh(vector<ofVec3f> point, float raito);
};



class Tetrakis : public GeometricShapes{
private:

    void initOrigin();
    vector<ofVec3f> originPoint;
    //ofMesh mesh;
    
    ofVec3f position;
    float raito;
    
    void divideMesh(ofVec3f point[4]);
    
    int numVertices;
    
public:
    
    Tetrakis(float _radius);
    void draw();
    void calcMesh();
    
    //setter getter
    void setRadius(float _radius);
    void setRaito(float _raito);
    
    float getRaito();
    void calcRaito();
    
};


class truncatedTetrahedron : public GeometricShapes{
private:
    //ofMesh mesh;
    ofVec3f position;
    //ofVec3f getNormal(ofVec3f points[3]);
    //ofColor makeColorFromPoint(ofVec3f point, int max);
    
    int fineness;
    int itr;
    
    float raito;
    float heightForHIH;
    int numRecursion;
public:
    truncatedTetrahedron(float _radius);
    
    void calcMesh();
    void draw();
    void reset();
    
    
    //setter
    void setPosition(ofVec3f _position);
    void setRadius(float _radius);
    
    void setFineness(int _fineness);
    void setItr(int _itr);
    
    void setRaito(float _raito);
    void setHeightForHIH(float _height);
    void setNumRecursion(int _numRecursion);
    
    
    
};


class Triakis : public GeometricShapes{
private:
    //var
    ofVec3f position;
    int mode;   //0: tetra, 1: octa, 2: Icosa
    int numRecursion;
    
    //ofMesh mesh;
    vector<ofVec3f> points;
    
    //func
    void initOrigin();
    void makeMesh(ofVec3f point[3]);
    float raito;
    ofVec3f getNormal(ofVec3f points[3]);
    ofColor makeColorFromPoint(ofVec3f point, int max);
    
    vector<ofVec3f> debugNormal;
    vector<ofVec3f> debugOrigin;
    
    void recursion(vector<ofVec3f> &pointForRecursion, int n);
    
    
    vector<ofVec3f> argForRecursion;
    bool debugOrNot = false;
    int modeRecursion = 0;
    
public:
    
    
    Triakis(float _radius);
    void draw();
    void calcMesh();
    
    void calcRaito();
    //setter
    void setPoisiton(ofVec3f _position);
    void setRadius(float _radius);
    void setMode(int _mode);
    void setRaito(float _raito);
    void setHeight(float _height);
    void setNumRecursion(int _numRecursion);
    void setModeRecursion(int _mode);
    
    //getter
    float getRaito();
    
    
    void debug();
    
};



#endif /* defined(__Koch3D__GeometricShapes__) */
